
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	const int MAX_CLUSTERS = 5;
	Vec3b colorTab[] =
	{
		Vec3b(255,255, 255),
		Vec3b(0, 0, 0),
		Vec3b(255, 100, 100),
		Vec3b(255, 0, 255),
		Vec3b(0, 255, 255)
	};
	Mat data, labels;
	Mat pic = imread("movie.jpg");
	for (int i = 0; i < pic.rows;i++)
		for (int j = 0; j < pic.cols; j++)
		{
			Vec3b point = pic.at<Vec3b>(i, j);
			Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			data.push_back(tmp);
		}

	//�������ͼƬ��ȷ��k��ֵ
	kmeans(data, 2, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
		3, KMEANS_RANDOM_CENTERS);

	int n = 0;
	//��ʾ����������ͬ������ò�ͬ����ɫ��ʾ
	for (int i = 0; i < pic.rows; i++)
		for (int j = 0; j < pic.cols; j++)
		{
			int clusterIdx = labels.at<int>(n);
			pic.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}

	imshow("pic", pic);
	waitKey(0);

	return 0;
}