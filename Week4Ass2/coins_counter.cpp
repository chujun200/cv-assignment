#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat binaryMat, labelMat, statsMat, centrMat, resultMat;
	Mat srcMat = imread("coin.png", 0);
	if (!srcMat.data) { cout << "Open failed, please check your Picture's address" << endl;return -1; }

	//Binarization and  Connected Component -getting
	threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);
	int nComp = connectedComponentsWithStats(binaryMat, labelMat, statsMat, centrMat, 8, CV_32S);

	//printf some information
	for (int i = 0; i < nComp; i++)
	{
		cout << "connected Components NO. " << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}
	cout << "the total of connected Components = " << nComp - 1 << endl;  //exclude background

	// Draw bounding box
	for (int i = 1; i < nComp; i++)
	{
		Rect bbx;
		bbx.x = statsMat.at<int>(i, 0);
		bbx.y = statsMat.at<int>(i, 1);
		bbx.width = statsMat.at<int>(i, 2);
		bbx.height = statsMat.at<int>(i, 3);
		rectangle(binaryMat, bbx, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	//Show the Picture 
	imshow("binaryMat", binaryMat);
	imshow("frame", srcMat);
	imwrite("result.jpg", binaryMat);
	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
