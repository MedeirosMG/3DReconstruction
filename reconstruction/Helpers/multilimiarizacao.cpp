#include "stdafx.h"
#include "../Helpers/multilimiarizacao.h"

std::vector<double> sortBackwards(std::vector<double> lim){

    int size = lim.size();

    for(int i=0; i<size; i++){
        lim[i] = -lim[i];
    }

    sort(lim.begin(),lim.end());

    for(int i=0; i<size; i++){
        lim[i] = -lim[i];
    }

    return lim;
}

Mat MultiLim(Mat im, std::vector<unsigned int> bests, int flag) {

	std::vector<unsigned int> limiares;

	int n_gray_values = bests.size() + 1;

	//cout << "gray values = " << n_gray_values;

	limiares.push_back(0);

	for (int i = 0; i< bests.size(); i++) {
		limiares.push_back(bests[i]);
	}

	limiares.push_back(255);

	int L = limiares.size();

	std::vector<double> lim;

	for (int i = 0; i<L; i++) {
		lim.push_back(i);
	}

	int quo = 0;
	if (flag) {
		lim = sortBackwards(lim);
		quo = lim[0] - lim[lim.size() - 1];
	}
	else {
		quo = lim[lim.size() - 1] - lim[0];
	}

	//      divide vector lim inteiro por max(lim) - min(lim)
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] / quo;
	}

	//    multiplica o vector inteiro por 255
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] * 255;
	}


	//backwards ta bugando nos proximos fors
	//    arredonda os valores do vector lim
	//int ja arredonda, porem tem que fazer ceil se for float
	int linhas = im.rows;
	int colunas = im.cols;
	int i = 0;
	int clust = 0;


	for (int y = 0; y<linhas; y++) {
		for (int x = 0; x<colunas; x++)
		{
			int anterior = 0;
			int proximo = 1;
			int t1 = limiares[anterior];
			int t2 = limiares[proximo];
			int index = 0;

			int pixelValue = (int)im.at<uchar>(y, x);
			while ( !((pixelValue >= t1) && (pixelValue <= t2)) )
			{
				anterior = proximo;
				proximo = proximo + 1;
				t1 = limiares[anterior];
				t2 = limiares[proximo];
				index++;
			}
			
			double cor = (double)index / (double)(limiares.size() - 1);
			if (flag)
			   im.at<uchar>(y, x) = (uchar)(cor*255);
			else
				im.at<uchar>(y, x) = (uchar)(255-(cor*255));
		}
	}

	return im;
}

Mat MultiLim2(Mat im, std::vector<unsigned int> bests, int flag) {

	std::vector<unsigned int> limiares;

	int n_gray_values = bests.size() + 1;

	limiares.push_back(0);

	for (int i = 0; i< bests.size(); i++) {
		limiares.push_back(bests[i]);
	}

	limiares.push_back(255);

	int L = limiares.size();

	std::vector<double> lim;

	for (int i = 0; i<L; i++) {
		lim.push_back(i);
	}

	int quo = 0;
	if (flag) {
		lim = sortBackwards(lim);
		quo = lim[0] - lim[lim.size() - 1];
	}
	else {
		quo = lim[lim.size() - 1] - lim[0];
	}

	//      divide vector lim inteiro por max(lim) - min(lim)
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] / quo;
	}

	//    multiplica o vector inteiro por 255
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] * 255;
	}


	//backwards ta bugando nos proximos fors
	//    arredonda os valores do vector lim
	//int ja arredonda, porem tem que fazer ceil se for float
	int linhas = im.rows;
	int colunas = im.cols;
	int i = 0;
	int clust = 0;


	for (int y = 0; y<linhas; y++) {
		for (int x = 0; x<colunas; x++)
		{
			int anterior = 0;
			int proximo = 1;
			int t1 = limiares[anterior];
			int t2 = limiares[proximo];
			int index = 0;

			int pixelValue = (int)im.at<uchar>(y, x);
			while (!((pixelValue >= t1) && (pixelValue <= t2)))
			{
				anterior = proximo;
				proximo = proximo + 1;
				t1 = limiares[anterior];
				t2 = limiares[proximo];
				index++;
			}

			double cor = (double)index / (double)(limiares.size() - 1);
			im.at<uchar>(y, x) = (uchar)(cor * 255);
		}
	}

	return im;
}

std::vector<Mat> SplitSegmentedRegions(Mat im, std::vector<unsigned int> bests, int flag)
{
	std::vector<unsigned int> limiares;

	int n_gray_values = bests.size() + 1;

	Mat im0(im.rows, im.cols, CV_8UC1, Scalar(0));

	std::vector<Mat> set_of_segmented_regions;
	for (int i = 0; i < n_gray_values; i++)
		set_of_segmented_regions.push_back(im0.clone());

	limiares.push_back(0);


	for (int i = 0; i< bests.size(); i++) {
		limiares.push_back(bests[i]);
	}

	limiares.push_back(255);


	int L = limiares.size();

	std::vector<double> lim;

	for (int i = 0; i<L; i++) {
		lim.push_back(i);
	}

	int quo = 0;
	if (flag) {
		lim = sortBackwards(lim);
		quo = lim[0] - lim[lim.size() - 1];
	}
	else {
		quo = lim[lim.size() - 1] - lim[0];
	}

	//Divide vector by (max(lim) - min(lim))
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] / quo;
	}

	//Multiplying vector by 255
	for (int i = 0; i<lim.size(); i++) {
		lim[i] = lim[i] * 255;
	}

	int linhas = im.rows;
	int colunas = im.cols;
	int i = 0;
	int clust = 0;


	for (int y = 0; y<linhas; y++) {
		for (int x = 0; x<colunas; x++)
		{
			int anterior = 0;
			int proximo = 1;
			int t1 = limiares[anterior];
			int t2 = limiares[proximo];
			int index = 0;

			int pixelValue = (int)im.at<uchar>(y, x);
			while (!((pixelValue >= t1) && (pixelValue <= t2)))
			{
				anterior = proximo;
				proximo = proximo + 1;
				t1 = limiares[anterior];
				t2 = limiares[proximo];
				index++;
			}

			double cor = (double)index / (double)(limiares.size() - 1);
			//im.at<uchar>(y, x) = (uchar)(cor * 255);
			set_of_segmented_regions[index].at<uchar>(y, x) = 255; // (uchar)(cor * 255);
		}
	}


	return set_of_segmented_regions;
}
