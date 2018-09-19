#ifndef ALGORITHMS_FIREFLY
#define ALGORITHMS_FIREFLY

#include <set>

#include "OpenCV.h"
#include "../Helpers/Tsallis.h"

using namespace std;
using namespace cv;
using namespace Helpers;

namespace Algorithms {

	class Firefly
	{
		private:
			Tsallis* _tsallis;

		public:
			Firefly();
			~Firefly();

			//Find image gray histogram
			void PsrGrayHist(Mat img, double H[], int L);

			//Creates a new alpha to reduce randomness
			double NewAlpha(double alpha, double delta);

			// Calculates distance between vectors
			double DistanceBetweenVectors(std::vector<unsigned int> &elem1, std::vector<unsigned int> &elem2);

			// Sort fireflies tresholds asc
			void ValidateThreshold(std::vector<std::vector<unsigned int> > &fireflies);

			// Calculates distance between fireflies
			std::vector<std::vector<double>> DistanceBetweenFireflies(std::vector<std::vector<unsigned int>> &fireflies);

			// Init fireflies matrix
			void Init_ffa(int n, int thresholds, int range, std::vector<std::vector<unsigned int> > &fireflies);

			// Moving fireflies towards the brightest one
			void Ff_move(double &beta, std::vector<std::vector<unsigned int>> &fireflies, std::vector<double> &lightn, double alpha, double gamma, int range, std::vector<std::vector<double>> a);

			void ChangeFireflies(std::vector<std::vector <unsigned int>> &fireflies, std::vector<unsigned int> index);

			void Tide_up(std::set<pair<double, unsigned int>> &zn, std::vector<unsigned int> &index, std::vector<double> &lightn);

			//Applies firefly, find thresholds
			std::vector<unsigned int> GaoFireflyThresholds(double* histograma, int hist_buff, int thresholds, int NFireFlies, int iter);

			//Find the best tresholds using firefly algorithm
			std::vector<unsigned int> BestsThresholds(Mat img, int thresholds, int n_fires, int itera);

	};

}

#endif