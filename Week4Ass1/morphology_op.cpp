#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("coin.png", 0) ;
	Mat binaryMat, erodeMat, dilateMat ,openingMat,closingMat;

	if (!srcMat.data) { cout << "Open failed, please check your Picture's address" << endl;return -1; }

	//Binarization 
	threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);
	//morphology-op
	Mat element = getStructuringElement(MORPH_RECT, Size(3,3));
	erode(binaryMat, erodeMat, element);
	dilate(binaryMat, dilateMat, element);
	morphologyEx(binaryMat, openingMat, MORPH_OPEN, element);
	morphologyEx(binaryMat, closingMat, MORPH_CLOSE, element);

	//Show the Picture 
	imshow("frame", srcMat);
	imshow("binaryMat", binaryMat);
	imshow("erode", erodeMat);
	imshow("dilate", dilateMat);
	imshow("opening", openingMat);
	imshow("closing", closingMat);
	
	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
