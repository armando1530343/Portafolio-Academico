#include <iostream>
#include <random>
#include <vector>
#include <float.h>
#include <algorithm>

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
int ngenes = 2;
double lbound = -1.5;
double ubound = 2.0;
// representacion del individuo
struct IND {
	vector<double> chrom;
	double fitness;

	IND() {
		chrom.resize(ngenes);

		for(auto& locus : chrom) {
			//locus = rnd::flip();
			locus = rnd::n_to_m_real(lbound, ubound);
		}
		//fitness
	}

	IND(const IND& ind) {
		chrom.resize(ngenes);
		copy(ind.chrom.begin(), ind.chrom.end(), chrom.begin());
		fitness = ind.fitness;
	}

	double operator[](int idx){
		return chrom[idx];
	}

	IND& operator=(const IND& ind) {
		chrom.resize(ngenes);
		copy(ind.chrom.begin(), ind.chrom.end(), chrom.begin());
		fitness = ind.fitness;
		return *this;
	}

	friend ostream& operator<<(ostream &os, const IND &ind){
		for(auto& i : ind.chrom) {
			os<<i<<" ";
		}
		os<<endl;
		return os;
	}


	void xover(IND &ind) {
		int xover_point = rnd::n_to_m_int(1, ngenes-2);
		cout<<xover_point<<endl;
		vector<int> tmp (ind.chrom.begin()+xover_point, ind.chrom.end());
		copy(chrom.begin()+xover_point, chrom.end(), ind.chrom.begin()+xover_point);
		copy(tmp.begin(), tmp.end(), chrom.begin()+xover_point);
	}

	//------------ cruza SBX ------------
	void xoverSBX(IND &ind){
		// se genera un numero aleatorio entre 0 y 1
		double u = .42;// rnd::n_to_m_int(0,1000) * .001;
		double nc = 2.0;
		double beta = (u <= .5) ? pow(2*u, 1 / (nc + 1)) : pow((1 / (2*(1 - u))) , 1 / (nc + 1));

		for (int i = 0; i < ngenes; ++i)
		{
			chrom[i] = .5 * ((chrom[i] + ind.chrom[i]) - beta*(abs(ind.chrom[i] - chrom[i])));
			ind.chrom[i] = .5 * ((chrom[i] + ind.chrom[i]) + beta*(abs(ind.chrom[i] - chrom[i])));
		}
	}

	void mutation(){
		double pm = 1.0/chrom.size();
		for(auto& i : chrom) {
			if(rnd::flip(pm))
				i = 1 - i;
		}
	}

	void mutationPBX(int t){
		int p = rnd::n_to_m_int(0, ngenes);
		double y = chrom[p];

		double u = rnd::n_to_m_int(0, 1000) * .001;
		double nm = 100 + t;
		double delta = ubound - lbound;
		double s = std::min(y - lbound, ubound - y) / delta;

		double sq = (u <= 0.5) ?  
		pow(2*u + ((1-2*u) * pow(1 - s, nm+1)), 1.0/(nm+1)) - 1:
		1 - pow(2*(1 - u) + 2*(u - .5)*pow(1 - s, nm+1), 1.0/(nm + 1));

		chrom[p] = y + sq*delta;

		//printf("p=%s\n", );

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

		//cout<<"hola"<<endl;

		//print_pop();

	}
	void evaluate(){

		//print_pop();
		
		double x[ngenes];
		static int flag(1);
		for(int i(0); i< pop_size; ++i) {
			pop[i].fitness = 0.0;
			for(int j(0); j<ngenes; ++j) {
				x[j] = pop[i][j];
				pop[i].fitness += x[j]*x[j];
			}
			printf("best:%f  fit: %f\n",best_ind.fitness, pop[i].fitness);
			if(flag == 1 || pop[i].fitness < best_ind.fitness) {
				best_ind = pop[i];
				flag = 0;
			}

		}
	}
	void ackley(){

		//print_pop();

		double x[ngenes];
		static int flag(1);
		for(int i(0); i< pop_size; ++i) {
			
			double x = pop[i][0];
			double y = pop[i][1];
			
			pop[i].fitness = -20*exp(-.2 * sqrt(.5 * (x*x + y*y))) 
			- exp(.5 * (cos(2*3.1415*x) + cos(2*3.1415*y))) + exp(1) + 20;
			
			//printf("best:%f  fit: %f  x:%f  y:%f\n",best_ind.fitness, pop[i].fitness, x, y);

			if(flag == 1 || pop[i].fitness < best_ind.fitness) {
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
			pop_new[i] = (pop[a].fitness < pop[b].fitness)? pop[a]:pop[b];
		}
	}
	void xover_and_mutation(int t){
		for (int i = 0; i < pop_size; i += 2)
		{
			//printf("chrom\n" );
			//cout << pop_new[i]<<endl;
			//cout << pop_new[i+1]<<endl;
			pop_new[i].xoverSBX(pop_new[i+1]);
			//printf("xover\n" );
			//cout << pop_new[i]<<endl;
			//cout << pop_new[i+1]<<endl;
			pop_new[i].mutationPBX(t);
			pop_new[i+1].mutationPBX(t);
			//printf("mutation\n" );
			//cout << pop_new[i]<<endl;
			//cout << pop_new[i+1]<<endl;
			//pop_new[i+1].mutation();
		}
	}
	void elitism(){
		int idx = rnd::n_to_m_int(0, pop_size-1);
		pop_new[idx] = best_ind;
	}
	void new_generation(){
		pop.swap(pop_new);
	}
	void print_pop(){
		//cout << "pop size:" << pop_size << " ngenes:" << ngenes << endl;
		for (int i = 0; i < 5; ++i){
			for (int j = 0; j < 2; ++j)
				cout << pop[i][j] << " ";
			cout<<endl;
		}
			//cout << i  << "\t" << pop[i].fitness << endl;
	}
	void print_pop_new(){
		cout << "Pop New:" << endl;
		for (int i = 0; i < pop_size; ++i)
			cout << i  << "\t" << pop_new[i].fitness << endl;
	}
	void run();
};

void SGA::run() {
	//evaluate();
	ackley();
	int t = 0;
	while(t < ngenerations){
		selection();
		xover_and_mutation(t);
		elitism();
		new_generation();
		ackley();
		//evaluate();
		++t;
		//cout<<best_ind<<" "<<best_ind[0]<<" "<<best_ind[1]<<" "
		//cout<<best_ind.fitness<<endl;
	}
	fprintf(stdout, "%f\n", best_ind.fitness);
	

}

int main(int argc, char const *argv[])
{

	/*
	
	Punto 2 (implementacion real):

	-cruzaSBX:		linea 84
	-mutacionPBX:	linea 105
	-func. ackley:	linea 164

	*/

	SGA sga;
	sga.run();

	return 0;
	
}
