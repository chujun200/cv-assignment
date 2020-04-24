#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;

float Euclid_Distance(float * a, float* b, int n);
void draw_His(Mat & src, int blockSize, int nX, int nY, float * hist);
void cal_His(Mat & mag, Mat & range, int blockSize, float * hist, int biasX, int biasY, int bias);

int main() {
	Mat refMat = imread("hogTemplate.jpg",0);
	Mat test_1 = imread("img1.jpg",0), test_2 = imread("img2.jpg",0);
	int blockSize = 16;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;
	int bins = 9*nX*nY;

	float * ref_hist = new float[bins];
	float * test1_hist = new float[bins];
	float * test2_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float)*bins);
	memset(test1_hist, 0, sizeof(float)*bins);
	memset(test2_hist, 0, sizeof(float)*bins);

	draw_His(refMat, blockSize, nX,  nY, ref_hist);
	draw_His(test_1, blockSize, nX, nY, test1_hist);
	draw_His(test_2, blockSize, nX, nY, test2_hist);
	float O_Dis1 = Euclid_Distance(ref_hist, test1_hist, bins);
	float O_Dis2 = Euclid_Distance(ref_hist, test2_hist, bins);
	delete[] ref_hist, test1_hist, test2_hist;
	cout << "Euclid_Distance of Pic1 " << (int)O_Dis1 << endl;
	cout << "Euclid_Distance of Pic2 " << (int)O_Dis2 << endl;
	//for (int i = 0;i < bins;i++) {
	//	cout << i<<":"<<ref_hist[i] << endl;
	//}
	return 0;
	/* the result is :
	Euclid_Distance of Pic1 188215776
	Euclid_Distance of Pic2 373521952
	Obviously ,Pic1 is closer to orignal picture! */

}
//----------Function to draw  histogram--------//
void draw_His(Mat & src, int blockSize, int nX,int nY, float * hist) {
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	int bias = 0;
	for (int i = 0; i < nY;i++) {
		for (int j = 0; j < nX;j++) {
			cal_His(mag, angle, blockSize, hist, j, i, bias);
			bias += 9;
		}
	}
}
/*----------draw histogram blocks by blocks--------
use biasX\biasY to calculate bias position of blocks
use bias to calculate bias of histogram tuple:
			*(hist + range + bias)               */
void cal_His(Mat & mag, Mat & angle, int blockSize,float * hist,int biasX, int biasY,int bias) {
	int bias_PicX = biasX * blockSize, bias_PicY = biasY * blockSize;
	for (int i = bias_PicX;i < blockSize + bias_PicX;i++) {
		for (int j = bias_PicY;j < blockSize + bias_PicY;j++) {
			int range = (angle.at<float>(i, j) -1) / 40;  //control range from 0-8
			*(hist + range + bias) += mag.at<float>(i, j);
		}
	}
}

float Euclid_Distance(float * a, float * b, int n) {
	float sum = 0;
	for (int i = 0; i < n;i++) {
		sum += pow((*(a + i) - *(b + i)), 2);
	}
	return sum;
}