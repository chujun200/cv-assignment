#include"TemplateMatch.h"

int main() {
	Mat refMat = imread("template.png", 0);
	Mat test = imread("img.png", 0);
	int blockSize = 12;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;
	int bins = 9 * nX*nY;

	//记录当前的最小响应以及对应位置
	double MinR =1e30;
	int nMinX;
	int nMinY;

	int nHeight = test.rows;
	int nWidth = test.cols;
	//模板的高、宽
	int nTplHeight = refMat.rows;
	int nTplWidth = refMat.cols;

	float * ref_hist = new float[bins];

	memset(ref_hist, 0, sizeof(float)*bins);
	draw_His(refMat, blockSize, nX, nY, ref_hist);
	std::cout << "Please wait,calculating..." << endl;
	for (int i = 0; i < nHeight - nTplHeight + 1; i++)
	{
		for (int j = 0; j < nWidth - nTplWidth + 1; )
		{
			//定义截取的矩形
			Rect rect(j,i,  nTplWidth,nTplHeight);
			Mat image_roi = test(rect);
			float * roi_hist = new float[bins];
			memset(roi_hist, 0, sizeof(float)*bins);
			draw_His(image_roi, blockSize, nX, nY, roi_hist);

			double O_Dis = Euclid_Distance(ref_hist, roi_hist, bins);
			//cout << O_Dis<<endl;
			if (O_Dis < MinR)
			{
				MinR = O_Dis;
				nMinX = j;
				nMinY = i;
			}
			delete[]  roi_hist;
			j = j + 5;
		}
		i = i + 5;
	}

	delete[] ref_hist;

	cout << "Euclid_Distance of Pic " << (int)MinR << endl;
	cout << "Min X position:" << nMinX << endl;
	cout << "Min Y position:" << nMinX;
	Rect rect(nMinX, nMinY, nTplWidth, nTplHeight);
	rectangle(test, rect, Scalar(255, 255, 255), 2, 8, 0);
	imshow("result",test);
	imwrite("result.png", test);
	waitKey(0);
	return 0;

}
