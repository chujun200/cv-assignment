#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;//实例化一个videocapture类，名称为cap
	cap.open(0);//
	if (!cap.isOpened())
	{
		std::cout << "不可打开视频文件" << std::endl;
		return -1;
	}

	Mat frame, bgMat, bny_subMat, subMat;
	int cnt = 0;
	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			frame.copyTo(bgMat);
		}
		else {
			absdiff(frame, bgMat, subMat);
			//imshow("image", frame);
			threshold(subMat, bny_subMat, 50, 255, THRESH_BINARY);

			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
				destroyAllWindows();
				return 0;
			}
		}
		cnt++;
	}
	return 0;

}