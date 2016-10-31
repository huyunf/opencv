#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	// Image
	cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);

	if (img.empty()) return -1;
	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img);

	cv::waitKey(0);
	cv::destroyWindow("Example1");

	// Video
	cv::VideoCapture cap;
	cap.open(string(argv[2]));

	if (!cap.isOpened()) { // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	// Get First Frame
	//------------------------------------------------------/
	cv::Mat img1;
	cap.read(img1);
	if (img1.empty()) return -1;
	cv::namedWindow("Example2", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example2", img1);
	cv::waitKey(0);
	cv::destroyWindow("Example2");

	// Get Many Frame
	//------------------------------------------------------/
	cv::Mat frame;
	cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
	while (1)
	{
		cap >> frame; if (!frame.data) break;
		cv::imshow("Example3", frame);
		cv::waitKey(0);
	}
	cv::destroyWindow("Example3");

	return 0;
}