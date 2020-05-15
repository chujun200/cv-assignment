#include <opencv2\opencv.hpp>    
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	float gamma;
	cout << "Please input gamma:";
	cin >> gamma;
	float Lut[256];

	for (int i = 0; i < 256; i++)
	{
		float temp = (float)i / 255;
		float temp2 = powf(temp, gamma);
		Lut[i] = temp2 * 255;   //归一化到0~255 
	}
	Mat image = imread("face.jpg");
	Mat imageGamma(image.size(), CV_32FC3);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			imageGamma.at<Vec3f>(i, j)[0] = Lut[image.at<Vec3b>(i, j)[0]];
			imageGamma.at<Vec3f>(i, j)[1] = Lut[image.at<Vec3b>(i, j)[1]];
			imageGamma.at<Vec3f>(i, j)[2] = Lut[image.at<Vec3b>(i, j)[2]];
			//imageGamma.at<Vec3f>(i, j)[0] = pow((double)(image.at<Vec3b>(i, j)[0]) / 255, gamma);
			//imageGamma.at<Vec3f>(i, j)[1] = pow((double)(image.at<Vec3b>(i, j)[1]) / 255, gamma);
			//imageGamma.at<Vec3f>(i, j)[2] = pow((double)(image.at<Vec3b>(i, j)[2]) / 255, gamma);
		}
	}
	 
	//转换成8bit图像显示   
	convertScaleAbs(imageGamma, imageGamma);
	imshow("src_pic", image);
	imshow("after_gamma", imageGamma);
	imwrite("伽马变换_0.5.jpg", imageGamma);
	waitKey();
	return 0;
}