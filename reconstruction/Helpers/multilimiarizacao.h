#ifndef MULTILIMIARIZACAO
#define MULTILIMIARIZACAO

#include <vector>
#include <algorithm>
#include "../Algorithms/OpenCV.h"
#include <iostream>

enum flag{

    backwards = 1,
    notbackwards = 0

};

std::vector<double> sortBackwards(std::vector<double> lim);

Mat MultiLim(Mat im, std::vector<unsigned int> bests, int flag);

Mat MultiLim2(Mat im, std::vector<unsigned int> bests, int flag);

std::vector<Mat> SplitSegmentedRegions(Mat im, std::vector<unsigned int> bests, int flag);

#endif // MULTILIMIARIZACAO

