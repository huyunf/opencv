#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
using namespace std;
int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *) 
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}
int main(int argc, char** argv) 
{
	cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
	if (argc == 1)
		g_cap.open(0);	// open the default camera
	else
		g_cap.open(string(argv[1]));

	if (!g_cap.isOpened()) { // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << " frames of dimensions("
		<< tmpw << ", " << tmph << ")." << endl;
	cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames,
		onTrackbarSlide);
	cv::Mat frame;
	while (1) 
	{
		if (g_run != 0) {
			g_cap >> frame; if (!frame.data) break;
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Example2_4", current_pos);

//#define SMOOTHED
#ifdef SMOOTHED
			// Create an image to hold the smoothed output
			cv::Mat out;
			// Do the smoothing
			// Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter().
			cv::GaussianBlur(frame, out, cv::Size(5, 5), 3, 3);
			cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);
			cv::imshow("Example2_4", out);
#else
			cv::imshow("Example2_4", frame);
#endif
			g_run -= 1;
		}
		char c = (char)cv::waitKey(10);
		if (c == 's') // single step
		{
			g_run = 1; cout << "Single step, run = " << g_run << endl;
		}
		if (c == 'r') // run mode
		{
			g_run = -1; cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27)
			break;
	}
	return(0);
}