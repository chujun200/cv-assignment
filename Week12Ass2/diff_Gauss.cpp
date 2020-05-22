#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void cal_Gauss_model(Mat * dataMats, Mat & Mean, Mat & Var,int num);
//计算高斯中的相关参数
void gauss_Thre(Mat & srcMat, Mat & dstMat, Mat & meanMat, Mat & varMat, float weight);
//对每一个点和他特定值值域进行二值化

int main()
{
	VideoCapture cap;//实例化一个videocapture类，名称为cap
	cap.open(0);//
	if (!cap.isOpened())
	{
		std::cout << "不可打开视频文件" << std::endl;
		return -1;
	}
	//存放背景的计算数据
	//Mat dataMats[500];
	Mat frame, meanMat, varMat; //均值与方差数据
	int cnt = 0, pic_num = 200;
	float weight = 2.5;
	Mat * dataMats = new Mat[pic_num];
	while (1)
	{
		cap >> frame;
		
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt < pic_num) {
			frame.copyTo(dataMats[cnt]);
			if (cnt == 0)
			{
				cout << "Gauss Modeling" << endl;
			}
		}
		else if (cnt == pic_num) {
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			cout << "data processing" << endl;
			cal_Gauss_model(dataMats, meanMat, varMat, pic_num);
			delete[] dataMats;
		}

		else {
			Mat resultMat;
			resultMat.create(frame.size(), CV_8UC1);
			gauss_Thre(frame, resultMat, meanMat,varMat,weight);
			imshow("result", resultMat);
			imshow("camera", frame);
			if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
				destroyAllWindows();
				return 0;
			}

		}
		cnt++;
	}
}

void cal_Gauss_model(Mat * dataMats, Mat & Mean, Mat & Var,int num) {
	int rows = dataMats[0].rows;
	int cols = dataMats[0].cols;

	for (int h = 0; h < rows; h++)
	{
		for (int w = 0; w < cols; w++)
		{

			int sum = 0;
			float var = 0;
			//求均值
			for (int i = 0; i < num; i++) {
				sum += dataMats[i].at<uchar>(h, w);
			}
			Mean.at<uchar>(h, w) = sum / num;
			//求方差
			for (int i = 0; i < num; i++) {
				var += pow((dataMats[i].at<uchar>(h, w) - Mean.at<uchar>(h, w)), 2);
			}
			Var.at<float>(h, w) = var / num;
		}
	}
}

void gauss_Thre(Mat & srcMat, Mat & dstMat, Mat & meanMat, Mat & varMat, float weight)
{
	int rows = srcMat.rows;
	int cols = srcMat.cols;

	for (int h = 0; h < rows; h++)
	{
		for (int w = 0; w < cols; w++)
		{
			int dif = abs(srcMat.at<uchar>(h, w)- meanMat.at<uchar>(h, w));
			int th = weight * varMat.at<float>(h, w);
			dstMat.at<uchar>(h, w) = (dif > th) ? 255 : 0;
		}
	}

}