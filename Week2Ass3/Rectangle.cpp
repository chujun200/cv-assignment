#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat scrMat = imread("image.jpg");
	Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 600;
	rect.height = 500;
	rectangle(scrMat, rect, Scalar(0, 0, 255), 5, 8, 0);
	imshow("Pic after rectangle", scrMat);

	while (true) {
		if (waitKey(30) == 27) {  //When key¡®Esc¡¯pressed£¬ exit.
			destroyAllWindows();
			return 0;
		}
	}
}