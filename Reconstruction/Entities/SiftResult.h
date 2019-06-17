#ifndef ENTITIES_RESULT_SIFT
#define ENTITIES_RESULT_SIFT

#include "../Algorithms/OpenCV.h"

namespace Entities {

	class SiftResult {
		public:
			vector<DMatch> Matches;
			vector<KeyPoint> FirstImageKeyPoints;
			vector<KeyPoint> SecondImageKeyPoints;
			SiftFeatureDetector detector;
			Mat firstImgDescription;
			Mat secondImgDescription;
			Mat siftImg;
			SiftResult();
			SiftResult(vector<DMatch> matches, vector<KeyPoint> firstImageKeyPoints, vector<KeyPoint> secondImageKeyPoints, SiftFeatureDetector detector, Mat firstDescriptor, Mat secondDescriptor);
			~SiftResult();
	};

}

#endif