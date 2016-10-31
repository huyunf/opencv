#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int start = cv::getCPUTickCount();
	
	//-----------------------------------------------------------------------------------------------------
	cv::Mat m;
	m.create(5, 5, CV_32FC1); // 3 rows, 10 columns of 3-channel 32-bit floats

	m.setTo(cv::Scalar(1.0f, 2.0f, 3.0f)); // 1st channel is 1.0, 2nd 0.0, 3rd 1.0

	cv::Mat n = cv::Mat::eye(5, 5, CV_32FC1);

	cv::Mat l(5, 5, CV_32FC1);

	cv::randu(l, -10, 10);

	cout << "Element(3, 3) is %f\n" << n.at<float>(2, 2) << endl;

	cout << l << endl << endl;

	cout << m << endl << endl;

	cout << n << endl << endl;

	cout << n.colRange(2, 4) << endl << endl;

	cout << n.diag(0) << endl << endl;

	cout << n(cv::Rect(1, 2, 3, 3)) << endl << endl;

	cout << n(cv::Range(0, 2), cv::Range(2, 5)) << endl << endl;

	cout << n + m + l<< endl << endl;

	//-----------------------------------------------------------------------------------------------------
	cv::Mat vec0(1, 5, CV_32FC1);
	cv::Mat vec1(1, 5, CV_32FC1);
	cv::Mat vecRes;

	cv::randu(vec0, -10, 10);
	cv::randu(vec1, -10, 10);

	cout << "vec0: " << vec0 << endl;
	cout << "vec1: " << vec1 << endl;

	cout << "abs(vec0): " << cv::abs(vec1) << endl;

	cv::absdiff(vec0, vec1, vecRes);
	cout << "absdiff(vec0, vec1): " << vecRes << endl;

	cv::addWeighted(vec0, 1.4, vec1, 0.8, 2.4, vecRes);
	cout << "addWeighted(vec0, vec1): " << vecRes << endl;

	cv::add(vec0, vec1, vecRes);
	cout << "add(vec0, vec1): " << vecRes << endl;

	cv::dct(vec0, vecRes);
	cout << "dct(vec0): " << vecRes << endl;

	cv::normalize(vec0, vecRes, 0.23, cv::NORM_L2);
	cout << "normalize(vec0): " << vecRes << endl;


	int end = cv::getCPUTickCount();

	cout << "start:" << start << " end:" << end << " diff:" << end - start << endl;

	return 0;
}