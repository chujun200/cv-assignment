#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat srcM = imread("image.jpg");
	Mat src,dst1,dst2;
	cvtColor(srcM, src, CV_RGB2GRAY);

	//Binarize the Picture
	adaptiveThreshold(src, dst1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);
	threshold(src, dst2, 100, 255, THRESH_BINARY);
	imshow("Binarization by adaptiveThreshold", dst1);
	imshow("Binarization by threshold", dst2);

	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
