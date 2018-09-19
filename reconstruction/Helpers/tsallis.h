
#ifndef HELPERS_TSALLIS
#define HELPERS_TSALLIS
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

namespace Helpers {

	class Tsallis
	{
		public:
			Tsallis();
			~Tsallis();

			double sumt = 0;

			double QValue(double *h, int buff_size);
			float TsallisEntropy(double *histograma, double q, int  a, int  b);
			double PsrAvaliacaoTsallis(double *histograma, double q, std::vector<unsigned int> idx_limiar, unsigned int buff_size);
			int MainTsallis(double *v);

		private:

	};

}

#endif // TSALLIS

