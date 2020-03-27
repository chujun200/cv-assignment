#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	//Mat frame, rframe, rrframe;

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	Mat frame,srcGray;//Gray Mat
	VideoCapture cap;

	//int ksize = 3;
	//double dx = 2, dy = 2;
	//double scale=1;
	//double delta=0;
	cap.open(0);
	if (!cap.isOpened()) { cout << "Open failed! Please check your camera or files!" << endl;return -1; }
	while (1)
	{
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			cout << "Frame can't be read" << std::endl;
			break;
		}
		else
		{
			cvtColor(frame, srcGray, CV_RGB2GRAY); //To gray picture

			Sobel(srcGray, grad_x, CV_16S, 1, 0, 3, 1, 1);
			convertScaleAbs(grad_x, abs_grad_x);
			//imshow("X-Sobel", abs_grad_x);

			Sobel(srcGray, grad_y, CV_16S, 0, 1, 3, 1, 1);
			convertScaleAbs(grad_y, abs_grad_y);
			//imshow("Y-Sobel", abs_grad_y);

			addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
			imshow("X-Y-Sobel", dst);

			//threshold(srcGray, rframe, 0, 255, CV_THRESH_OTSU);
			//Sobel(rframe, rframe, -1, dx, 0, ksize);
			//Sobel(rframe, rrframe, -1, 0, dy, ksize);
			//imshow("frame ", rrframe);
		}
		if (waitKey(30) == 27) { destroyAllWindows();break; }
	}
	return 0;
}