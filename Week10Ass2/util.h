#pragma once
#include <opencv.hpp>

using namespace cv;
using namespace std;

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
int selectPolygon(cv::Mat srcMat, cv::Mat &dstMat);
int mouseROI();
double dftDemo(cv::Mat &padded, cv::Mat &mag, cv::Mat &ph);
int ifftDemo(Mat &mag, Mat &ph, Mat &src, Mat &padded, double maxVal, Mat &dspMat);
