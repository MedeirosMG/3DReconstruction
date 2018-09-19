#ifndef HELPERS_MULTITHRESHOLD
#define HELPERS_MULTITHRESHOLD

#include <vector>
#include <algorithm>
#include "../Algorithms/OpenCV.h"
#include <iostream>

namespace Helpers {

	class MultiThreshold
	{
		public:
			MultiThreshold();
			~MultiThreshold();

			std::vector<double> SortBackwards(std::vector<double> lim);
			Mat MultiLim(Mat im, std::vector<unsigned int> bests, int flag);
			Mat MultiLim2(Mat im, std::vector<unsigned int> bests, int flag);
			std::vector<Mat> SplitSegmentedRegions(Mat im, std::vector<unsigned int> bests, int flag);

		private:

	};

}

enum FlagMultiThreshold{
    backwards = 1,
    notbackwards = 0
};

#endif // MULTILIMIARIZACAO

