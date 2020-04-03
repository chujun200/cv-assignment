#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat src_Mat = imread("lena.jpg");
	Mat dstMat;

	const Point2f src_Mat_pt[] = {
		Point2f(150,150),
		Point2f(150,300),
		Point2f(350,300),
		Point2f(350,150) };
	const Point2f dst_pt[] = {
		Point2f(200,150),
		Point2f(200,300),
		Point2f(340,270),
		Point2f(340,180) };

	Mat perspective_matrix = getPerspectiveTransform(src_Mat_pt, dst_pt);//返回一个3*3的矩阵，代表pts2-->pts1的映射
	warpPerspective(src_Mat, dstMat, perspective_matrix, src_Mat.size());

	imshow("src_Mat1", src_Mat);
	imshow("src_Mat2", dstMat);
	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
