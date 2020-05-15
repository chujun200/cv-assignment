#include <opencv2\opencv.hpp>    
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "Image_after_gamma"        
void on_gamma(int gamma_100, void* data);
int main()
{
	Mat image = imread("gtest.jpg");
	int gamma_100;
	//creat windows and Track bar
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("Threshold", WINDOW_NAME, &gamma_100, 200, on_gamma, &image);
	on_gamma(100, &image);  //Initialize Call_Back

	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}


void on_gamma(int gamma_100, void* data)
{
	float gamma = (float)gamma_100 / 100;
	float Lut[256];

	for (int i = 0; i < 256; i++)
	{
		float temp = (float)i / 255;
		float temp2 = powf(temp, gamma);
		Lut[i] = temp2 * 255;   //归一化到0~255 
	}

	Mat image = *(Mat*)data;
	Mat imageGamma(image.size(), CV_32FC3);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			imageGamma.at<Vec3f>(i, j)[0] = Lut[image.at<Vec3b>(i, j)[0]];
			imageGamma.at<Vec3f>(i, j)[1] = Lut[image.at<Vec3b>(i, j)[1]];
			imageGamma.at<Vec3f>(i, j)[2] = Lut[image.at<Vec3b>(i, j)[2]];
		}
	}

	//转换成8bit图像显示   
	convertScaleAbs(imageGamma, imageGamma);
	imwrite("after_gamma.jpg", imageGamma);
	imshow(WINDOW_NAME, imageGamma);  //Update image

}