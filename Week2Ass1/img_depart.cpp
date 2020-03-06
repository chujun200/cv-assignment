#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat scrMat = imread("ͼƬ1.png");
	// define the vector
	vector<Mat> channels;
	split(scrMat, channels);

	imshow("Blue", channels.at(0));
	imshow("Green", channels.at(1));
	imshow("Red", channels.at(2));

	while (true) {
		if (waitKey(30) == 27) {  //When key: 'Esc'pressed, exit.
			destroyAllWindows();
			return 0;
		}
	}

}
