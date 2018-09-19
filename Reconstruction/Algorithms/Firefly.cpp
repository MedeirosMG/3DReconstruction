#include "stdafx.h"

#include "Firefly.h"

using namespace std;
using namespace cv;

namespace Algorithms {

	Firefly::Firefly()
	{
		_tsallis = new Tsallis();
	}

	Firefly::~Firefly()
	{
	}

	// Find image gray histogram
	void Firefly::PsrGrayHist(Mat img, double H[], int L)
	{
		int linhas = img.rows;
		int colunas = img.cols;

		for (int i = 0; i < L; i++)  H[i] = 0;

		for (int y = 0; y < linhas; y++) {
			for (int x = 0; x < colunas; x++) {

				int pixelValue = (int)img.at<uchar>(y, x);

				H[pixelValue] = H[pixelValue] + 1;
			}
		}

		for (int i = 0; i < L; i++) {
			H[i] = H[i] / (linhas*colunas);
		}

	}

	// Creates a new alpha to reduce randomness
	double Firefly::NewAlpha(double alpha, double delta) {

		alpha = alpha*delta;
		return alpha;
	}

	// Calculates distance between vectors
	double Firefly::DistanceBetweenVectors(std::vector<unsigned int> &elem1, std::vector<unsigned int> &elem2) {

		std::vector<double> aux;
		std::vector<double> aux2;

		double soma = 0;

		for (unsigned int i = 0; i < elem1.size(); i++) {
			int vai = elem1[i] - elem2[i];
			aux.push_back(vai);
		}

		for (unsigned int i = 0; i < elem1.size(); i++) {
			int vai = pow(aux[i], 2);
			aux2.push_back(vai);
		}

		for (unsigned int i = 0; i < elem1.size(); i++) {
			soma += aux2[i];
		}

		return (sqrt(soma));
	}

	// Sort fireflies tresholds asc
	void Firefly::ValidateThreshold(std::vector<std::vector<unsigned int> > &fireflies) { //ok
		//fireflies: matrix where rows are fireflies and columns are theirs thresholds 

		for (unsigned int i = 0; i < fireflies.size(); i++) {
			sort(fireflies[i].begin(), fireflies[i].end());
		}
	}

	// Calculates distance between fireflies
	std::vector<std::vector<double>> Firefly::DistanceBetweenFireflies(std::vector<std::vector<unsigned int>> &fireflies) {

		std::vector<std::vector <double> > all_dist;

		all_dist.resize(fireflies.size());

		for (unsigned int i = 0; i < fireflies.size(); i++) {
			all_dist[i].resize(fireflies.size());
		}

		for (unsigned int i = 0; i < all_dist.size(); i++) {
			for (unsigned int j = 0; j < all_dist.size(); j++) {
				all_dist[i][j] = 0.0;
			}
		}

		for (unsigned int i = 0; i < all_dist.size(); i++) {
			for (unsigned int j = 0; j < all_dist.size(); j++) {
				all_dist[i][j] = DistanceBetweenVectors(fireflies[i], fireflies[j]);
			}
		}
		return all_dist;
	}

	// Init fireflies matrix
	void Firefly::Init_ffa(int n, int thresholds, int range, std::vector<std::vector<unsigned int>> &fireflies) {
		//n - number of fireflies
		//thresholds - numbers of thresholds

		//if commented the algorithm will be pseudorandom
		//srand(time(NULL));

		int* v = new int[range];

		for (int i = 0; i < n; i++)
		{
			// fill array with numbers from 0 to range - 1
			for (int t = 0; t < range; t++) {
				v[t] = t;
			}
			int aux = 0;
			int temp = 0;

			// shuffle array numbers randomly
			for (int t2 = 0; t2 < range; t2++) {
				aux = std::rand() % range;
				temp = v[t2];
				v[t2] = v[aux];
				v[aux] = temp;
			}

			for (int j = 0; j < thresholds; j++) {
				fireflies[i][j] = v[j];
			}
		}
		ValidateThreshold(fireflies);
	}

	// Moving fireflies towards the brightest one
	void Firefly::Ff_move(double &beta, std::vector<std::vector<unsigned int>> &fireflies, std::vector<double> &lightn, double alpha, double gamma, int range, std::vector<std::vector<double>> a)
	{
		//if commented the algorithm will be pseudorandom 
		//srand(time(NULL));
		int* v = new int[fireflies[0].size()];
		double  beta0 = 1;
		int ni = fireflies.size(); // number of fireflies

		for (int i = 0; i < ni; i++)
		{
			for (int j = 0; j < ni; j++)
			{
				if (lightn[j] > lightn[i])
				{
					beta0 = 1.0;
					beta = beta0*exp((-gamma)*pow(a[i][j], 2));

					for (unsigned int t = 0; t < fireflies[0].size(); t++)
					{
						v[t] = alpha*(std::rand() % 256);
					}

					if (i != ni)
					{
						for (unsigned int k = 0; k < fireflies[0].size(); k++)
						{

							fireflies[i][k] = ((1 - beta)*(fireflies[i][k])) + ((beta)*(fireflies[j][k])) + v[k];
							fireflies[i][k] = fireflies[i][k] / (1.0 + alpha);
						}
					}
				}
			}
		}

		ValidateThreshold(fireflies);
	}

	// muda_fireflies
	void Firefly::ChangeFireflies(std::vector<std::vector <unsigned int>> &fireflies, std::vector<unsigned int> index) {

		std::vector<std::vector<unsigned int> > new_fireflies(fireflies.size(), std::vector<unsigned int>(fireflies[0].size(), 0));

		for (unsigned int i = 0; i < fireflies.size(); i++) {
			for (unsigned int j = 0; j < fireflies[0].size(); j++) {
				new_fireflies[i][j] = fireflies[i][j];
			}
		}

		for (unsigned int i = 0; i < fireflies.size(); i++) {
			for (unsigned int j = 0; j < fireflies[0].size(); j++) {
				fireflies[i][j] = new_fireflies[index[i]][j];
			}
		}

	}

	// tide_up
	void Firefly::Tide_up(std::set<pair<double, unsigned int>> &zn, std::vector<unsigned int> &index, std::vector<double> &lightn) {

		std::set<pair<double, unsigned int> >::iterator it;
		int i = 0;
		for (it = zn.begin(); it != zn.end(); it++) {
			lightn[i] = it->first * (-1);
			i++;
		}

		i = 0;
		for (it = zn.begin(); it != zn.end(); it++) {
			index[i] = it->second;
			i++;
		}
	}

	// Applies firefly, find thresholds
	std::vector<unsigned int> Firefly::GaoFireflyThresholds(double* histograma, int hist_buff, int thresholds, int NFireFlies, int iter)
	{
		int n = NFireFlies; // number of fireflies
		int MaxGeneration = iter; // max generation of fireflies
		double beta = 0;
		std::vector<std::vector<unsigned int> > fireflies; //fireflies matrix
		fireflies.resize(n, std::vector<unsigned int>(thresholds, 0));
		std::vector<double> lightn(n, 0); //vector that holds fireflies light
		std::vector<unsigned int> melhor(thresholds, 0);
		std::vector<unsigned int> index(n, 0);
		std::vector<unsigned int> bests; //bests tresholds
		double alpha = 0.01;
		double gamma = 1.0;
		double delta = 0.97;

		//initializing fireflies with random thresholds
		Init_ffa(n, thresholds, hist_buff, fireflies);
		std::set<pair<double, unsigned int> > zn;

		std::vector<std::vector<double>> all_dist(n, std::vector<double>(n, 0));

		for (int i = 0; i < MaxGeneration; i++) {
			zn.clear();


			for (int h = 0; h < n; h++) {
				pair<double, int > p((_tsallis->PsrAvaliacaoTsallis(histograma, 0.35, fireflies[h], thresholds)*(-1)), h);
				zn.insert(p);
			}

			Tide_up(zn, index, lightn);

			//putting the best firefly on first row of the matrix
			ChangeFireflies(fireflies, index);

			//finding distance between fireflies
			for (int a = 0; a < n; a++) {
				for (int b = 0; b < n; b++) {
					all_dist[a][b] = DistanceBetweenVectors(fireflies[a], fireflies[b]);
				}
			}

			//moves fireflies to brightest one
			Ff_move(beta, fireflies, lightn, alpha, gamma, 256, all_dist);

			//find new alpha
			alpha = NewAlpha(alpha, delta);

			for (int v = 0; v < thresholds; v++) {
				melhor[v] = fireflies[0][v];
			}
		}

		bests = melhor;

		return bests;
	}

	// Find the best tresholds using firefly algorithm
	std::vector<unsigned int> Firefly::BestsThresholds(Mat img, int thresholds, int n_fires, int itera)
	{
		// gray histogram array
		double* H = new double[256];
		std::vector<unsigned int> bests;

		// process the gray histogram of the image and throw it on array
		PsrGrayHist(img, H, 256);

		// put the bests thresholds on vector bests
		bests = GaoFireflyThresholds(H, 256, thresholds, n_fires, itera);

		return bests;
	}

}