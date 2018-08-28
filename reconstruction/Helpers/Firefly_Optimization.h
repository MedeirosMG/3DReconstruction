#ifndef FIREFLY_OPTIMIZATION_H
#define FIREFLY_OPTIMIZATION_H

#include "../Algorithms/OpenCV.h"
#include <set>


using namespace std;
using namespace cv;

//Find image gray histogram
void psrGrayHist(Mat img, double H[], int L);

//Creates a new alpha to reduce randomness
double newAlpha(double alpha, double delta);

// Calculates distance between vectors
double dist(std::vector<unsigned int> &elem1, std::vector<unsigned int> &elem2);

// Sort fireflies tresholds asc
void validaThresholds(std::vector<std::vector<unsigned int> > &fireflies);

// Calculates distance between fireflies
std::vector<std::vector<double> > distancias(std::vector<std::vector<unsigned int> > &fireflies);

// Init fireflies matrix
void init_ffa(int n, int thresholds, int range, std::vector<std::vector<unsigned int> > &fireflies);

// Moving fireflies towards the brightest one
void ff_move(double &beta, std::vector<std::vector<unsigned int> > &fireflies, std::vector<double> &lightn, double alpha, double gamma, int range, std::vector<std::vector<double> > a);

void muda_fireflies(std::vector<std::vector <unsigned int> > &fireflies, std::vector<unsigned int> index);

void tide_up(std::set<pair<double, unsigned int> > &zn, std::vector<unsigned int> &index, std::vector<double> &lightn);

//Applies firefly, find thresholds
std::vector<unsigned int> gaoFireflyThresholds(double* histograma, int hist_buff, int thresholds, int NFireFlies, int iter);

//Find the best tresholds using firefly algorithm
std::vector<unsigned int> beststhresholds(Mat img, int thresholds, int n_fires, int itera);

#endif