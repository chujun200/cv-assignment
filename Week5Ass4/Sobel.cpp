#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat frame, rframe, rrframe;
	Mat srcGray;//Gray Mat
	VideoCapture cap;

	int ksize = 9;
	double dx = 2, dy = 2;
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
			threshold(srcGray, rframe, 0, 255, CV_THRESH_OTSU);
			Sobel(rframe, rrframe, -1, dx, dy, ksize);
			imshow("frame ", rrframe);
		}
		if (waitKey(30) == 27) { destroyAllWindows();break; }
	}
	return 0;
}