#include <opencv2/opencv.hpp>  //ͷ�ļ�
#define THRESHOLD 100;
using namespace cv;  //����cv�����ռ�
using namespace std;
int  main()
{
	// ��1������һ��ͼƬ������ͼ��
	Mat srcImage = imread("image.jpg");
	int height = srcImage.rows;
	int width = srcImage.cols;
	uchar threshold = THRESHOLD;
		for (int j = 0;j < height;j++)
		{
			for (int i = 0; i < width; i++)
			{
				// ��2������ÿ������
				uchar average = (srcImage.at<Vec3b>(j, i)[0] + srcImage.at<Vec3b>(j, i)[1] + srcImage.at<Vec3b>(j, i)[2]) / 3;
				average = (average > threshold) ? 255 : 0;
				srcImage.at<Vec3b>(j, i)[0] = average;
				srcImage.at<Vec3b>(j, i)[1] = average;
				srcImage.at<Vec3b>(j, i)[2] = average;
			}
		}
		// ��3��չʾͼƬ
		imshow("����ֵ����", srcImage);
		// ��4���ȴ����ⰴ������
		waitKey(0);
	return 0;
}