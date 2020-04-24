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
	int bins = 8*nX*nY;

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
	cout << "Euclid_Distance of Pic1 " << O_Dis1 << endl;
	cout << "Euclid_Distance of Pic2 " << O_Dis2 << endl;
	//for (int i = 0;i < bins;i++) {
	//	cout << i<<":"<<ref_hist[i] << endl;
	//}
	delete[] ref_hist, test1_hist, test2_hist;
	return 0;
}

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
			bias += 8;
		}
	}
}

void cal_His(Mat & mag, Mat & angle, int blockSize,float * hist,int biasX, int biasY,int bias) {
	for (int i = biasX * blockSize;i < blockSize + biasX * blockSize;i++) {
		for (int j = biasY * blockSize;j < blockSize + biasY * blockSize;j++) {
			int range = angle.at<float>(i, j) / 40;
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