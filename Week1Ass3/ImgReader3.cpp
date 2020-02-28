#include <opencv2/opencv.hpp>  //头文件
#define THRESHOLD 100;
using namespace cv;  //包含cv命名空间
using namespace std;
int  main()
{
	// 【1】读入一张图片，载入图像
	Mat srcImage = imread("image.jpg");
	int height = srcImage.rows;
	int width = srcImage.cols;
	uchar threshold = THRESHOLD;
		for (int j = 0;j < height;j++)
		{
			for (int i = 0; i < width; i++)
			{
				// 【2】处理每个像素
				uchar average = (srcImage.at<Vec3b>(j, i)[0] + srcImage.at<Vec3b>(j, i)[1] + srcImage.at<Vec3b>(j, i)[2]) / 3;
				average = (average > threshold) ? 255 : 0;
				srcImage.at<Vec3b>(j, i)[0] = average;
				srcImage.at<Vec3b>(j, i)[1] = average;
				srcImage.at<Vec3b>(j, i)[2] = average;
			}
		}
		// 【3】展示图片
		imshow("【二值化】", srcImage);
		// 【4】等待任意按键按下
		waitKey(0);
	return 0;
}