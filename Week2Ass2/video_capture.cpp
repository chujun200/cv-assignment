#include<opencv2\opencv.hpp>
#include<iostream>

#ifndef OpenMode 
	#define OpenMode 0
#endif // !OpenMode   OpenMode will be the camera number or the address of file.

using namespace cv;
using namespace std;


int main() 
{
	VideoCapture cap;
	cap.open(OpenMode);

	if (!cap.isOpened()) 
	{
		cout << "Open failed! Please check your camera or files!" << endl;
		return -1;
	}
	//Some data-get code should be here£¡//
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;

	//Visualize the Image
	while (true)
	{
		Mat frame;
		if (!cap.read(frame))
		{
			std::cout << "Frame can't be read" << std::endl;
			break;
		}
		else
		{
			imshow("frame", frame);
			if (waitKey(30) == 27) {  //When key¡®Esc¡¯pressed£¬ exit.
				destroyAllWindows();
				return 0;
			}
		}
	}
}