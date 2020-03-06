#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

float His_counter(Mat & img, float * histgram, int size) {
	int height = img.rows;
	int width = img.cols;
	int num_total = height * width;
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width; j++)
		{
			histgram[img.at<uchar>(i, j)]++;
		}
	}
	int max_val=0;  //compare to get max color and its index
	for (int i = 0; i < size; i++)
	{
		max_val = (histgram[i] > max_val) ? histgram[i] : max_val;
		histgram[i] /= num_total;
	}
	return  saturate_cast<float>(max_val)/ saturate_cast<float>(num_total);
	//return relative max color val  ;
}


void draw_Histogram(Mat & img, float * histgram, int size,float maxValue) {
	//usage:draw the Histogram. With histgram value, maxValue and size.
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < size; i++)
	{
		float binValue = histgram[i]; 
		//expand Value from 0 to size_max
		int realValue = saturate_cast<int>(binValue / maxValue *  hpt);
		line(img, Point(i, size - 1), Point(i, size - realValue), Scalar(255));
	}
}


int main() {
	int  size = 256;
	float max_val , histgram[256] = { 0 };

	Mat scrMat = imread("image.jpg", 0);
	if (!scrMat.data) {
		cout << "Open failed, please check your Picture's address" << endl;
		return -1;
	}

	Mat dstImage(size, size, CV_8U, Scalar(0));

	max_val = His_counter(scrMat, histgram, size);
	draw_Histogram(dstImage, histgram,size, max_val);

	imshow("Histogram", dstImage);

	while (true) {
		if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
			destroyAllWindows();
			return 0;
		}
	}
	return 0;
}