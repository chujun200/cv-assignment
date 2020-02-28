#include <opencv2/opencv.hpp>  //ͷ�ļ�
#define THRESHOLD 100;
using namespace cv;  //����cv�����ռ�

int main()
{
	// ��1������һ��ͼƬ������ͼ��
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
			// ��2������ÿ������
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			average = (average > threshold) ? 255 : 0;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	// ��3��չʾͼƬ
	imshow("����ֵ����", srcMat);
	imshow("��ǳ������", shallowMat);
	imshow("�������", deepMat);

	// ��4���ȴ����ⰴ������
	waitKey(0);
	return 0;
}