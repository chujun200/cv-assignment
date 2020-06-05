
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void kmeans_mask(Mat & pic, Mat & Mask);

const int MAX_CLUSTERS = 5;
Vec3b colorTab[] =
{
	Vec3b(255,255, 255),
	Vec3b(0, 0, 0),
	Vec3b(255, 100, 100),
	Vec3b(255, 0, 255),
	Vec3b(0, 255, 255)
};

int main()
{
	string bg_addr = "bg.mp4";
	string dr_addr = "dragon.mp4";
	VideoCapture cap,cap2;
	cap.open(dr_addr);//
	cap2.open(bg_addr);
	if (!cap.isOpened())
	{
		std::cout << "open failed" << std::endl;
		return -1;
	}
	Mat frame, rframe, Mask;   //dragon
	Mat frame2, rframe2, Mask2;   //background
	Mat result;
	int cnt = 0;
	while (1) {
		cap >> frame;
		cap2 >> frame2;
		if (!cap.read(frame))
		{
			std::cout << "All frames have been read!" << std::endl;
			break;
		}
		else if (cnt > 220) {
			return 0;
		}
		else
		{
			resize(frame2 ,frame2,Size(320, 568));

			//get  bg mask
			kmeans_mask(frame, Mask);
			//mask it and mix them
			frame.copyTo(rframe, Mask);
			bitwise_not(Mask, Mask2);
			frame2.copyTo(rframe2, Mask2);
			result = rframe + rframe2;
			imshow("1", result);

			//clear rframe，rframe2
			bitwise_xor(rframe,rframe, rframe);
			bitwise_xor(rframe2, rframe2, rframe2);
			waitKey(10);

		}
		cnt++;
	}


	return 0;
}

void kmeans_mask(Mat & pic, Mat & Mask) {
	//return background mask

	Mat data, labels;
	for (int i = 0; i < pic.rows;i++)
		for (int j = 0; j < pic.cols; j++)
		{
			Vec3b point = pic.at<Vec3b>(i, j);
			Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			data.push_back(tmp);
		}

	//k=
	kmeans(data, 2, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
		3, KMEANS_RANDOM_CENTERS);
	int n = 0;
	//显示聚类结果，不同的类别用不同的颜色显示
	pic.copyTo(Mask);
	for (int i = 0; i < pic.rows; i++)
		for (int j = 0; j < pic.cols; j++)
		{
			int clusterIdx;
			if ( (labels.at<int>( (pic.rows*pic.cols)-1) ) ==0)
			{
				clusterIdx = 1 - labels.at<int>(n);
			}
			else {
				clusterIdx = labels.at<int>(n);
			}
			Mask.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}
}