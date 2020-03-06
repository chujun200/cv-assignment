#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

float His_counter(Mat & img, float * histgram, int size) {
	int height = img.rows;
	int width = img.cols;
	float num_total = height * width;
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width; j++)
		{
			histgram[img.at<uchar>(i, j)]++;
		}
	}
	int max_val = 0;  //compare to get max color and its index
	for (int i = 0; i < size; i++)
	{
		max_val = (histgram[i] > max_val) ? histgram[i] : max_val;
		histgram[i] /= num_total;
	}
	return  saturate_cast<float>(max_val)/ saturate_cast<float>(num_total);
	//return relative max color val  ;
}

int main() {
	Mat scrMat = imread("image.jpg", 0);
	int size=256;
	float max_num, histgram[256] = {0};
	max_num = His_counter(scrMat, histgram ,size);
	for (int i = 0; i < size; i++)
	{
		cout <<"The number of "<<i<< " is: " << histgram[i] << endl;
	}
	cout << "The max color number is " << max_num << endl;
	return 0;

}