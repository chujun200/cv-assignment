#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat frame, rframe;
	VideoCapture cap;
	int ksize = 3;
	cap.open(0);
	if (!cap.isOpened()){cout << "Open failed! Please check your camera or files!" <<endl;return -1;}
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
			medianBlur(frame, rframe, ksize);
			imshow("frame ", rframe);
		}
		if (waitKey(30) == 27) { destroyAllWindows();break; }
	}
	return 0;
}