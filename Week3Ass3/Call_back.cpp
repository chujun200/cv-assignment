#include <opencv2\opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Image_show"        

//-----------------------------------[Call_Back Function]------------------------------------
void on_Threshold(int th, void* data)
{
	Mat src = *(Mat*)data, dst;
	threshold(src, dst, th, 255, 0);  //Call threshold func	
	imshow(WINDOW_NAME, dst);  //Update image
}

int main()
{
	int g_nThresholdValue = 100;
	Mat srcMat, g_Mat;

	//Image-Reader
	srcMat = imread("image.jpg");
	if (!srcMat.data) { cout << "Open failed, please check your Picture's address" << endl;return -1; }
	imshow("Orignal Pic", srcMat);
	cvtColor(srcMat, g_Mat, COLOR_RGB2GRAY);

	//creat windows and Track bar
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("Threshold", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold, &g_Mat);
	on_Threshold(100, &g_Mat);  //Initialize Call_Back

	// Wait for exit  ; When key: 'Esc'pressed, exit.
	while (1) { if (waitKey(30) == 27) { destroyAllWindows();break; } }
	return 0;
}
