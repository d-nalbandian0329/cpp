#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main() {
	cv::Mat mat = cv::imread("sample.jpg", cv::IMREAD_COLOR);
	cv::namedWindow("sample", cv::WINDOW_AUTOSIZE);
	cv::imshow("sample", mat);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
