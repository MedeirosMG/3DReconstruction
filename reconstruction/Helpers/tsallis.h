
#ifndef TSALLIS
#define TSALLIS
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>

using namespace std;

double sumt = 0;

double qValue(double *h, int buff_size);

float TsallisEntropy(double *histograma, double q, int  a, int  b);

double psrAvaliacaoTsallis(double *histograma, double q, std::vector<unsigned int >idx_limiar, unsigned int buff_size);

int mainTsallis(double *v);
#endif // TSALLIS

