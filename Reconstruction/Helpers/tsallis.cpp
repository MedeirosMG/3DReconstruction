#include "stdafx.h"
#include "Tsallis.h"

namespace Helpers {

	Tsallis::Tsallis()
	{
	}

	Tsallis::~Tsallis()
	{
	}

	double Tsallis::QValue(double *h, int buff_size) {

		int n = buff_size;
		long double Rmin = 9999999999999.0;

		double R = 0, N, S = 0, Smax = 0, qopt = 0;

		for (float q = 0.1; q <= 0.9; q += 0.05) {
			N = 0;

			for (int i = 0; i < n; i++) {
				N = N + pow(h[i], q);
			}

			S = (1.0 - N) / (q - 1.0);

			Smax = (1.0 - n*pow((1.0 / (double)n), q)) / (q - 1.0);

			R = S / Smax;

			if (R < Rmin) {
				Rmin = R;
				qopt = q;
			}
		}

		qopt = 0.35;
		return qopt;
	}

	float Tsallis::TsallisEntropy(double *histograma, double q, int  a, int  b) {

		int L = b - a + 1;
		double sum = 0;
		double* H = new double[L];

		for (int h = 0; h < L; h++) {
			H[h] = 0;
		}

		int j = 0;
		for (int i = a; i <= b; i++) {
			H[j] = histograma[i];
			j++;
		}

		for (int i = 0; i < L; i++) {
			sum = sum + H[i];
		}

		sum = sum + 1;
		for (int i = 0; i < L; i++) {
			H[i] = H[i] / sum;
		}

		q = QValue(histograma, L);
		double ret = 0;

		for (int i = 0; i < L; i++) {
			if (H[i] != 0) {
				ret = ret + pow(H[i], q);
			}
		}

		double S;

		S = (1 - ret) / (q - 1);

		delete(H);

		return S;

	}

	double Tsallis::PsrAvaliacaoTsallis(double *histograma, double q, std::vector<unsigned int> idx_limiar, unsigned int buff_size) {

		double light = 0;
		int n = buff_size + 2;

		std::vector<int> lim;

		lim.push_back(0);

		for (int i = 0; i < buff_size; i++) {
			lim.push_back(idx_limiar[i]);
		}
		lim.push_back(255);

		int a = lim[0];
		int b = lim[1];

		light = TsallisEntropy(histograma, q, a, b);

		double TE;
		double Plight = light;

		for (int i = 2; i < n; i++) {
			a = b + 1;
			b = lim[i];
			TE = TsallisEntropy(histograma, q, a, b);
			if (TE != 0) {
				light = light + TE;
				Plight = Plight * TE;
			}
		}

		light = light + (1 - q)* Plight;

		lim.clear();
		//    cout<<"Tsallis : "<<light<<endl;
		return light;
	}

	int Tsallis::MainTsallis(double *v) {

		if (!v)return -1;

		double aux = 0;

		for (int i = 0; i < 256; i++) {
			aux = aux + v[i];
		}

		for (int i = 0; i < 256; i++)  v[i] = v[i] / aux;

		std::vector<unsigned int> limiares;

		limiares.push_back(79);

		limiares.push_back(159);

		double a = PsrAvaliacaoTsallis(v, 0.5, limiares, 2);

		cout << "a == " << a << endl;

		return 0;
	}

}