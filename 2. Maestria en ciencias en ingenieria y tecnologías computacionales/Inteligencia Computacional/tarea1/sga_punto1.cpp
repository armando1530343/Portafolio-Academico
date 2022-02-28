#include <iostream>
#include <random>
#include <vector>
#include <float.h>

using namespace std;
namespace rnd {
static auto dev = random_device();
static auto gen = mt19937{dev()};
static auto dist_0_1 = uniform_real_distribution<double>(0,1);

bool flip(const double p = 0.5) {
    return (dist_0_1(gen) < p);
}

template <typename T = int>
T n_to_m_int(const T n, const T m) {
    auto dist_n_m_int = uniform_int_distribution<T>(n,m);
    return (dist_n_m_int(gen));
}

template <typename T = double>
T n_to_m_real(const T n, const T m) {
    auto dist_n_m_real = uniform_real_distribution<T>(n,m);
    return (dist_n_m_real(gen));
}
};

//parameteros
int L = 12;
int ngenes = 2;
double lbound = -1.5;
double ubound = 2.0;
// representacion del individuo
struct IND {
	vector<int> chrom;
	double fitness;

	IND() {
		chrom.resize(L*ngenes);

		for(auto& locus : chrom) {
			locus = rnd::flip();
		}
		//fitness
	}

	IND(const IND& ind) {
		chrom.resize(L*ngenes);
		copy(ind.chrom.begin(), ind.chrom.end(), chrom.begin());
		fitness = ind.fitness;
	}
	double decode(int idx) {
		double phenotype = 0.0;
		for(int i(0); i<L; ++i){
			phenotype += ldexp(chrom[idx*L + i], i);
		}
		double val = lbound + (phenotype/(pow(2.0, L)-1.0)) * (ubound - lbound);
		return val;
	}
	double operator[](int idx){
		return decode(idx);
	}


	IND& operator=(const IND& ind) {
		chrom.resize(L*ngenes);
		copy(ind.chrom.begin(), ind.chrom.end(), chrom.begin());
		fitness = ind.fitness;
		return *this;
	}

	friend ostream& operator<<(ostream &os, const IND &ind){
		for(auto& i : ind.chrom) {
			os<<i;
		}
		os<<endl;
		return os;
	}


	void xover(IND &ind) {
		int xover_point = rnd::n_to_m_int(1, L*ngenes-2);
		//cout<<"punto de cruce: "<<xover_point<<endl;
		vector<int> tmp (ind.chrom.begin()+xover_point, ind.chrom.end());
		copy(chrom.begin()+xover_point, chrom.end(), ind.chrom.begin()+xover_point);
		copy(tmp.begin(), tmp.end(), chrom.begin()+xover_point);
	}

	void xover2point(IND &ind) {
		//cout<<"genes:"<<L*ngenes<<endl;
		int xover_point1 = rnd::n_to_m_int(1, L*ngenes-2);
		int xover_point2 = rnd::n_to_m_int(xover_point1, L*ngenes-2);
		//cout<<"punto de cruce 1: "<<xover_point1<<endl;
		//cout<<"punto de cruce 2: "<<xover_point2<<endl;

		/*cout << "genes cruce 1: ";
		for (int i = xover_point1; i <= xover_point2; ++i)
			cout << chrom[i];
		cout<<endl;
		cout << "genes cruce 2: ";
		for (int i = xover_point1; i <= xover_point2; ++i)
			cout << ind.chrom[i];
		cout<<endl;*/
		
		vector<int> tmp (ind.chrom.begin()+xover_point1, ind.chrom.begin()+xover_point2);
		copy(chrom.begin()+xover_point1, chrom.begin()+xover_point2, ind.chrom.begin()+xover_point1);
		copy(tmp.begin(), tmp.end(), chrom.begin()+xover_point1);
	}

	void mutation(){
		double pm = 1.0/chrom.size();
		for(auto& i : chrom) {
			if(rnd::flip(pm))
				i = 1 - i;
		}
	}
};

//el algoritmo genetico

class SGA {
	int pop_size = 80;
	int ngenerations = 20;
	vector<IND> pop;
	vector<IND> pop_new;
	IND best_ind;
public:
	SGA() {
		pop.resize(pop_size);
		pop_new.resize(pop_size);
		best_ind.fitness = DBL_MAX;
	}
	void evaluate(){
		double x[ngenes];
		static int flag(1);
		for(int i(0); i< pop_size; ++i) {
			pop[i].fitness = 0.0;
			for(int j(0); j<ngenes; ++j) {
				x[j] = pop[i][j];
				pop[i].fitness += x[j]*x[j];
			}
			if(flag == 1 || pop[i].fitness > best_ind.fitness) {
				best_ind = pop[i];
				flag = 0;
			}

		}
	}
	void ackley(){
		double x[ngenes];
		static int flag(1);
		for(int i(0); i< pop_size; ++i) {
			
			double x = pop[i][0];
			double y = pop[i][1];
			
			pop[i].fitness = -20*exp(-.2 * sqrt(.5 * (x*x + y*y))) 
			- exp(.5 * (cos(2*3.1415*x) + cos(2*3.1415*y))) + exp(1) + 20;
			
			//printf("best:%f  fit: %f\n",best_ind.fitness, pop[i].fitness);

			if(flag == 1 || pop[i].fitness > best_ind.fitness) {
				best_ind = pop[i];
				flag = 0;
			}

		}
	}
	
	void selection(){
		for (int i = 0; i < pop_size; ++i)
		{
			int a = rnd::n_to_m_int(0, pop_size-1);
			int b = rnd::n_to_m_int(0, pop_size-1);
			//cout << "a:" << pop[a].fitness << " b:" << pop[b].fitness << endl;
			pop_new[i] = (pop[a].fitness < pop[b].fitness)? pop[a]:pop[b];
			//cout << "a:" << pop[a].fitness << " b:" << pop[b].fitness << " best:" << pop_new[i].fitness << endl;
		}
	}

	// ---- SELECCION POR RULETA ----
	void roulette_selection(){

		double roulette[pop_size];
		double sum = 0.0;
		//cout << "Roulette:" << endl;
		for (int i = 0; i < pop_size; ++i)
		{
			sum += pop[i].fitness;
			roulette[i] = sum;
			//cout << roulette[i] << endl;
		}

		for (int i = 0; i < pop_size; ++i)
		{
			int a = rnd::n_to_m_int(0, int(sum));
			int b = rnd::n_to_m_int(0, int(sum));
			int a_=0, b_=0;
			//int j = 0;
			for (int j = 0; j < pop_size-1; j++)
			{
				if(a <= roulette[j])
					a_ = j;
				if(b <= roulette[j])
					b_ = j;
			}
			//pop_new[i] = pop[b];
			pop_new[i] = (pop[a_].fitness > pop[b_].fitness)? pop[a_]:pop[b_];
			//cout << i << "\t" << roulette[i] << "\t" << r << "\t" << b << "\tnew:" << pop_new[i] << endl;
		}
	}

	void xover_and_mutation(){
		for (int i = 0; i < pop_size; i += 2)
		{
			pop_new[i].xover2point(pop_new[i+1]);
			pop_new[i].mutation();
			pop_new[i+1].mutation();
		}
	}
	void elitism(){
		int idx = rnd::n_to_m_int(0, pop_size-1);
		pop_new[idx] = best_ind;
	}
	void new_generation(){
		pop.swap(pop_new);
	}
	void run();
};

void SGA::run() {
	//ackley();
	evaluate();
	int t = 0;
	while(t < ngenerations){
	  roulette_selection();
	  //selection();
	  xover_and_mutation();
	  elitism();
	  new_generation();
	  evaluate();
	  //ackley();
	  ++t;
	  //cout<<best_ind<<" "<<best_ind[0]<<" "<<best_ind[1]<<" "
	  //cout<<best_ind.fitness<<endl;

	}
	fprintf(stdout, "%f\n", best_ind.fitness);
	

}

int main(int argc, char const *argv[])
{

	/*

	Punto 1 (implementacion binaria):

	-Seleccion por ruleta:	linea 182
	-Cruza de dos puntos:	linea 90
	-func. ackley:			linea 150

	*/

	SGA sga;
	sga.run();

	return 0;
	
}
