#include <opencv2/opencv.hpp>  //ͷ�ļ�
using namespace cv;  //����cv�����ռ�

void main()
{
	// ��1������һ��ͼƬ������ͼ��
	Mat srcImage = imread("image.jpg");
	Mat srcImage2 = imread("image.jpg",0);
	int height = srcImage.rows;
	int width = srcImage.cols;
	
	for (int j = 0;j < height;j++)
	{
		for (int i = 0; i < width; i++)
		{
	// ��2������ÿ������
			uchar average = (srcImage.at<Vec3b>(j, i)[0] + srcImage.at<Vec3b>(j, i)[1] + srcImage.at<Vec3b>(j, i)[2]) / 3;
			srcImage.at<Vec3b>(j, i)[0] = average;
			srcImage.at<Vec3b>(j, i)[1] = average;
			srcImage.at<Vec3b>(j, i)[2] = average;
		}
	}
	// ��3��չʾͼƬ	 ��4���ȴ����ⰴ������
	imshow("��ƽ������ͼ��", srcImage);
	imshow("���Ҷ�ͼ��", srcImage2);
	waitKey(0);
}