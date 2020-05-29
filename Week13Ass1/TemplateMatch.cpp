#include"TemplateMatch.h"

//----------Function to draw  histogram--------//
void draw_His(Mat & src, int blockSize, int nX, int nY, float * hist) {
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
void cal_His(Mat & mag, Mat & angle, int blockSize, float * hist, int biasX, int biasY, int bias) {
	int bias_PicX = biasX * blockSize, bias_PicY = biasY * blockSize;
	for (int i = bias_PicX;i < blockSize + bias_PicX;i++) {
		for (int j = bias_PicY;j < blockSize + bias_PicY;j++) {
			int range = (angle.at<float>(j, i)) / 40;  //control range from 0-8
			*(hist + range + bias) += mag.at<float>(j,i);
		}
	}
}

double Euclid_Distance(float * a, float * b, int n) {
	double sum = 0;
	for (int i = 0; i < n;i++) {
		sum += abs(*(a + i) - *(b + i));
	}
	return sum;
}
