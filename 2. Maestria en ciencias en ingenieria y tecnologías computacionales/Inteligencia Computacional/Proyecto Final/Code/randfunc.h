/* Funciones para el manejo de números aleatorios, de genetic.c
   Sin modificar, salvo randomize para recibir la semilla desde
   la invocación. */

#include <math.h>

int jrand;
double oldrand[55];
double rndx2;
int rndcalcflag;
void warmup_random(float);
float rndreal(float, float);
int rnd(int, int);
float randomperc(void);
double randomnormaldeviate(void);
void randomizef(double);
double noise(double,double);
void initrandomnormaldeviate(void);
int flip(float);
void advance_random(void);

/* Flip a biased coin - true if heads */

int flip(float prob)

{
    if(randomperc() <= prob)
	return(1);
    else
	return(0);

}

/* Fetch a single random number between 0.0 and 1.0 - Subtractive Method */
/* See Knuth, D. (1969), v. 2 for details */
/* name changed from random() to avoid library conflicts on some machines*/

float randomperc()

{
    jrand++;

    if(jrand >= 55)
    {
	jrand = 1;
	advance_random();
    }

    return((float) oldrand[jrand]);
}

/* Create next batch of 55 random numbers */

void advance_random()

{
    int j1;
    double new_random;

    for(j1 = 0; j1 < 24; j1++)
    {
	new_random = oldrand[j1] - oldrand[j1+31];
	if(new_random < 0.0) new_random = new_random + 1.0;
	oldrand[j1] = new_random;
    }

    for(j1 = 24; j1 < 55; j1++)
    {
	new_random = oldrand [j1] - oldrand [j1-24];
	if(new_random < 0.0) new_random = new_random + 1.0;
	oldrand[j1] = new_random;
    }

}

/* Initialize random numbers batch */

void randomizef(double semilla)

{
    int j1;

    for(j1=0; j1<=54; j1++)
	 oldrand[j1] = 0.0;

    jrand=0;

    warmup_random(semilla);
}

/* Get random off and running */

void warmup_random(float random_seed)

{
    int j1, ii;
    double new_random, prev_random;

    oldrand[54] = random_seed;
    new_random = 0.000000001;
    prev_random = random_seed;

    for(j1 = 1 ; j1 <= 54; j1++)

    {
	ii = (21*j1)%54;
	oldrand[ii] = new_random;
	new_random = prev_random-new_random;
	if(new_random<0.0) new_random = new_random + 1.0;
	prev_random = oldrand[ii];
    }

    advance_random();
    advance_random();
    advance_random();

    jrand = 0;

}

/* Pick a random integer between low and high */

int rnd(int low, int high)

{
    int i;

    if(low >= high)
	i = low;

    else

    {
	i = (randomperc() * (high - low + 1)) + low;
	if(i > high) i = high;
    }

    return(i);
}

/* real random number between specified limits */

float rndreal(float lo ,float hi)

{
    return((randomperc() * (hi - lo)) + lo);
}

/* normal noise with specified mean & std dev: mu & sigma */

double noise(double mu,double sigma)

{
    return((randomnormaldeviate()*sigma) + mu);
}

/* random normal deviate after ACM algorithm 267 / Box-Muller Method */

double randomnormaldeviate()

{
    double t, rndx1;

    if(rndcalcflag)
    {
	rndx1 = sqrt(- 2.0*log((double) randomperc()));
	t = 6.2831853072 * (double) randomperc();
	rndx2 = sin(t);
	rndcalcflag = 0;
	return(rndx1 * cos(t));
    }

    else

    {
	rndcalcflag = 1;
	return(rndx2);
    }

}

/* initialization routine for randomnormaldeviate */

void initrandomnormaldeviate()

{
    rndcalcflag = 1;
}
