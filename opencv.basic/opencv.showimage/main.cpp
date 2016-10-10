#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function
#include <iostream>

#define SHOW_IMAGE
#define CANNY_CHECK

int main(int argc, char** argv) 
{
#ifdef SHOW_IMAGE
	cv::Mat img = cv::imread(argv[1], -1);
	cv::Mat img2;
	if (img.empty()) return -1;
	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img);
//#define Gblur_DS
#ifdef Gblur_DS
	cv::pyrDown(img, img2);
	cv::imshow("Example2", img2);
#endif	
	cv::waitKey(0);
	cv::destroyWindow("Example1");
#endif

#ifdef CANNY_CHECK
	cv::Mat img_rgb = cv::imread(argv[1]);
	cv::Mat img_gry, img_cny;
	cv::cvtColor(img_rgb, img_gry, CV_RGB2GRAY);
	cv::namedWindow("Example Gray", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Example Canny", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example Gray", img_gry);
	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow("Example Canny", img_cny);
	cv::waitKey(0);

	int x = 16, y = 32;
	cv::Vec3b intensity = img_rgb.at< cv::Vec3b >(y, x);
	uchar blue = intensity.val[0]; // We could write img_rgb.at< cv::Vec3b >(x,y)[0]
	uchar green = intensity.val[1];
	uchar red = intensity.val[2];
	cv::Mat img_pyr, img_pyr2;

	cv::pyrDown(img_gry, img_pyr);
	cv::pyrDown(img_pyr, img_pyr2);
	cv::Canny(img_pyr2, img_cny, 10, 100, 3, true);

	std::cout << "At (x,y) = (" << x << ", " << y <<
		"): (blue, green, red) = (" <<
		(unsigned int)blue <<
		", " << (unsigned int)green << ", " <<
		(unsigned int)red << ")" << std::endl;
	std::cout << "Gray pixel there is: " <<
		(unsigned int)img_gry.at<uchar>(x, y) << std::endl;
	x /= 4; y /= 4;
	std::cout << "Pyramid2 pixel there is: " << (unsigned int)img_pyr2.at<uchar>(x, y) << std::endl;
	img_cny.at<uchar>(x, y) = 128; // Set the Canny pixel there to 128
#endif
}