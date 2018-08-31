#ifndef ENTITIES_RESULT_SIFT
#define ENTITIES_RESULT_SIFT

#include "../Algorithms/OpenCV.h"

namespace Entities {

	class ResultSift {
		public:
			vector<DMatch> Matches;
			vector<KeyPoint> FirstImageKeyPoints;
			vector<KeyPoint> SecondImageKeyPoints;
			ResultSift();
			ResultSift(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints);
			~ResultSift();
	};

}

#endif