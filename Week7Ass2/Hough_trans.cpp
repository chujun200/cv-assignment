#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat src_M = imread("metal-part-distorted-03.png"), g_Mat, e_Mat;
	imshow("src", src_M);
	Canny(src_M, e_Mat, 50, 200, 3);
	//cvtColor(e_Mat, g_Mat, CV_RGB2GRAY);

	//----------- Hough trans------------//

	//----------- First out way: Mat ------------//
	Mat line_Mat;
	HoughLines(e_Mat, line_Mat, 1, CV_PI / 180, 100, 0, 0);
	for (int i = 0; i < line_Mat.rows; i++)
	{
		float rho = line_Mat.at<Vec2f>(i)[0], theta = line_Mat.at<Vec2f>(i)[1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = saturate_cast<int>(y0 - 1000 * (a));

		line(src_M, pt1, pt2, Scalar(255, 255, 255), 1, CV_AA);
	}

	//----------- Second out way: vector ------------//
	//vector<Vec2f> lines;
	//HoughLines(e_Mat, lines, 1, CV_PI / 180, 100, 0, 0);
	//for (int i = 0; i < lines.size(); i++)
	//{
	//	float rho = lines[i][0], theta = lines[i][1];
	//	Point pt1, pt2;
	//	double a = cos(theta), b = sin(theta);
	//	double x0 = a * rho, y0 = b * rho;
	//	pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
	//	pt1.y = saturate_cast<int>(y0 + 1000 * (a));
	//	pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
	//	pt2.y = saturate_cast<int>(y0 - 1000 * (a));

	//	line(src_M, pt1, pt2, Scalar(255, 255, 255), 1, CV_AA);
	//}

	imshow("result", src_M);
	imwrite("HoughLines.jpg", src_M);
	//When key: 'Esc'pressed, exit.
	while (1) {
		if (waitKey(30) == 27) { destroyAllWindows();return 0; }
	}
}