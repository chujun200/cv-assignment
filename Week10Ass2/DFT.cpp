#include <opencv.hpp>
#include"util.h"
using namespace cv;
using namespace std;

int main() {
	Mat dst1,dst2,dst;
	Mat src1 = imread("./testImages\\Einstein.jpg", 0);
	Mat src2 = imread("./testImages\\Monroe.jpg", 0);

	int m = getOptimalDFTSize(src1.rows); //2,3,5的倍数有更高效率的傅里叶变换
	int n = getOptimalDFTSize(src1.cols);
	Mat padded1, padded2;
	//把灰度图像放在左上角,在右边和下边扩展图像,扩展部分填充为0;
	copyMakeBorder(src1, padded1, 0, m - src1.rows, 0, n - src1.cols, BORDER_CONSTANT, Scalar::all(0));
	copyMakeBorder(src2, padded2, 0, m - src2.rows, 0, n - src2.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat mag1 = Mat_<float>(padded1), ph1 = Mat_<float>(padded1);
	Mat mag2 = Mat_<float>(padded2), ph2 = Mat_<float>(padded2);
	double maxVal1, maxVal2;

	maxVal1 = dftDemo(padded1, mag1, ph1);
	maxVal2 = dftDemo(padded2, mag2, ph2);

	Mat mask1,mask2;
	selectPolygon(mag1, mask1);
	mag1 = mag1.mul(mask1);
	ph1 = ph1.mul(mask1);
	ifftDemo(mag1, ph1, src1, padded1, maxVal1, dst1);
	imshow("1", dst1);

	//selectPolygon(mag2, mask2);
	mask2 = 1 - mask1;
	ph2 = ph2.mul(mask1);
	ifftDemo(mag2, ph2, src2, padded2, maxVal2, dst2);
	imshow("2", dst2);

	addWeighted(dst1, 0.4, dst2, 0.6, 0, dst);
	imshow("dst_final", dst);
	imwrite("dst_final.jpg", dst);

	return 0;
}