#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int gammaCorrection(cv::Mat srcMat, cv::Mat & dstMat, float gamma)
{
	if (srcMat.channels() != 1)return -1;
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
		float inten = (float)i;
	}

	srcMat.copyTo(dstMat);

	MatIterator_<uchar> it, end;
	for (it = dstMat.begin<uchar>(), end = dstMat.end<uchar>(); it != end; it++) {
		*it = lut[(*it)];
	}
	return 0;
}
int main()
{
	cv::Mat srcMat = imread("C://project/gtest.jpg", 0);
	cv::Mat dstMat;
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return -1;
	}
	float gamma = 0.5;
	gammaCorrection(srcMat, dstMat, gamma);
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	destroyAllWindows();
	return 0;
}