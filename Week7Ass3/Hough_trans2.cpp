#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat src_M = imread("metal-part-distorted-03.png"), g_Mat, ga_Mat,e_Mat;
	imshow("src", src_M);
	Canny(src_M, e_Mat, 50, 200, 3);

	cvtColor(src_M, g_Mat, COLOR_BGR2GRAY);


	//----------- Hough------------//

	//----------- First out way: Mat ------------//
	Mat line_Mat;
	HoughLinesP(e_Mat, line_Mat, 1, CV_PI / 180, 40, 50, 10);
	for (int i = 0; i < line_Mat.rows; i++)
	{
		Vec4i  l = line_Mat.at<Vec4i>(i);
		line(src_M, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, CV_AA);
	}

	//----------- Second out way: vector ------------//
	//vector<Vec4i> lines;
	//HoughLinesP(e_Mat, lines, 1, CV_PI / 180, 40, 50, 10);

	//for (int i = 0; i < lines.size(); i++)
	//{
	//	Vec4i l = lines[i];
	//	line(src_M, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 1, CV_AA);
	//}



	imshow("result", src_M);
	imwrite("HoughLines.jpg", src_M);
	//When key: 'Esc'pressed, exit.
	while (1) {
		if (waitKey(30) == 27) { destroyAllWindows();return 0; }
	}
}