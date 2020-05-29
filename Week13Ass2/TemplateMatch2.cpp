
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//调用本地摄像头
int main()
{
	VideoCapture cap;//实例化一个videocapture类，名称为cap
	cap.open(0);//
	if (!cap.isOpened())
	{
		std::cout << "open failed" << std::endl;
		return -1;
	}
	long cnt = 0;
	Mat frame;
	Mat templateMat;
	Mat resultMat;
	while (1) {
		cap >> frame;
		if (cnt == 0)
		{
			Rect2d r = selectROI(frame);
			
			destroyAllWindows();
			frame(r).copyTo(templateMat);
		}
		else {//matchTemlate
			resultMat.create(frame.rows - templateMat.rows, frame.cols - templateMat.cols, CV_32FC1);//遍历
			matchTemplate(frame, templateMat, resultMat, TM_CCOEFF_NORMED);
			normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

			Point min, max;
			double minVal, maxVal;
			minMaxLoc(resultMat, &minVal, &maxVal, &min, &max, Mat());
			rectangle(frame, Rect(max.x, max.y, templateMat.cols, templateMat.rows), Scalar(255, 0, 0));
			imshow("resultMat", resultMat);
			imshow("template", templateMat);
			imshow("frame", frame);

		}
		if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
			destroyAllWindows();
			return 0;
		}
		cnt++;
	};

	return 0;
}
