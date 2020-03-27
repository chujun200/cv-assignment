#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) { cout << "Open failed! Please check your camera or files!" << endl;return -1; }

	double scale = 1.5;
	//Defin Threshold of H S V
	double i_minh = 0, i_maxh = 20;  //·ôÉ«
	double i_mins = 43, i_maxs = 255;
	double i_minv = 100, i_maxv = 255;

	while (1)
	{
		Mat frame, hsvMat, detectMat, G_Mat , disp_Mat;
		// Usage: Original\ To HSV \ Binaryzation and Mask\ For GaussianBlur \ show final Picture
		Size ksize = Size(5,5);
		double sigmaX = 3;
		double sigmaY = 3;
		cap >> frame;

		//-----------Binaryzation------------//
		Size resimgsize = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(resimgsize, frame.type());
		resize(frame, rFrame, resimgsize, INTER_LINEAR);
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);
		inRange(hsvMat, Scalar(i_minh, i_mins, i_minv), Scalar(i_maxh, i_maxs, i_maxv), detectMat);

		//-----------GaussianBlur------------//
		GaussianBlur(rFrame, G_Mat, ksize, sigmaX, sigmaY);
		rFrame.copyTo(disp_Mat);
		G_Mat.copyTo(disp_Mat,detectMat);   //Mask 

		//-----------Picture-Show------------//
		imshow("while :in the range", detectMat);
		imshow("display", disp_Mat);
		imshow("frame", rFrame);

		//When key: 'Esc'pressed, exit.
		if (waitKey(30) == 27) { destroyAllWindows();return 0; }
	}
}


