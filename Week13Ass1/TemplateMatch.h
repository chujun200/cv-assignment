#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

double Euclid_Distance(float * a, float* b, int n);
void draw_His(Mat & src, int blockSize, int nX, int nY, float * hist);
void cal_His(Mat & mag, Mat & range, int blockSize, float * hist, int biasX, int biasY, int bias);
