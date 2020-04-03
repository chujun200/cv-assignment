#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat srcMat =  imread("lena.jpg");
	Mat dstMat;
	if (!srcMat.data) { cout << "Open failed, please check your Picture's address" << endl;return -1; }

	//define three points to get Affine  matrix
	const Point2f src_pt[] = {
		Point2f(200,200),
		Point2f(250,200),
		Point2f(200,100) };
	const Point2f dst_pt[] = {
		Point2f(300,100),
		Point2f(300,50),
		Point2f(200,100) };

	const Mat  affine_matrix = getAffineTransform(src_pt, dst_pt);
	cout << "affine_matrix=\n" << affine_matrix << endl;
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
