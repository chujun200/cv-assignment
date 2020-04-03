#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat srcMat =  imread("lena.jpg");
	Mat dstMat;
	if (!srcMat.data) { cout << "Open failed, please check your Picture's address" << endl;return -1; }

	//define angle\scale\center to get Affine  matrix
	float angle = -10.0, scale = 1;
	Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	cout << "affine_matrix=\n" << affine_matrix << endl;
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size(), INTER_CUBIC);

	imshow("src", srcMat);
	imshow("dst", dstMat);
	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
