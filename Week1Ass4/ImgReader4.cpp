#include <opencv2/opencv.hpp>  //头文件
#define THRESHOLD 100;
using namespace cv;  //包含cv命名空间

int main()
{
	// 【1】读入一张图片，载入图像
	Mat srcMat = imread("image.jpg");
	Mat deepMat, shallowMat= srcMat;
	srcMat.copyTo(deepMat);
	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = THRESHOLD;
	for (int j = 0;j < height;j++)
	{
		for (int i = 0; i < width; i++)
		{
			// 【2】处理每个像素
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			average = (average > threshold) ? 255 : 0;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	// 【3】展示图片
	imshow("【二值化】", srcMat);
	imshow("【浅拷贝】", shallowMat);
	imshow("【深拷贝】", deepMat);

	// 【4】等待任意按键按下
	waitKey(0);
	return 0;
}