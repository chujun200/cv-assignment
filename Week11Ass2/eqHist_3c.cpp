#include <opencv2\opencv.hpp>    
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat scrMat = imread("etest.jpg"), dstMat;
	int height = scrMat.rows;
	int width = scrMat.cols;
	// define the vector
	vector<Mat> temp,channels;
	split(scrMat, temp);
	split(scrMat, channels);
	equalizeHist(temp.at(0), channels.at(0));
	equalizeHist(temp.at(1), channels.at(1));
	equalizeHist(temp.at(2), channels.at(2));

	merge(channels, dstMat);
	imshow("after-equalize", dstMat);
	imwrite("after-equalize.jpg", dstMat);
	//imshow("Blue", channels.at(0));
	//imshow("Green", channels.at(1));
	//imshow("Red", channels.at(2));
	waitKey(0);
	
	return 0;
}