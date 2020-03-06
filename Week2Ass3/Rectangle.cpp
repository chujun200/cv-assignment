#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat scrMat = imread("image.jpg");
	Rect rect;
	Point pt, pt1, pt2;
	pt.x = 100;
	pt.y = 100;
	pt1.x = 50;
	pt1.y = 50;
	pt2.x = 100;
	pt2.y = 100;
	rect.x = 100;
	rect.y = 100;
	rect.width = 600;
	rect.height = 500;
	circle(scrMat, pt, 50, Scalar(0, 0, 255), 1, 8, 0);
	line(scrMat, pt1,pt2, Scalar(0, 0, 255));
	rectangle(scrMat, rect, Scalar(0, 0, 255), 5, 8, 0);
	imshow("Pic after rectangle", scrMat);

	while (true) {
		if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
			destroyAllWindows();
			return 0;
		}
	}
}