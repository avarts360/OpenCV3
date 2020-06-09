#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	 
	cv::namedWindow("Video_cam", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Video_cam_pyrDown", cv::WINDOW_AUTOSIZE);

	cv::VideoCapture capture;

	if (argc == 1) {
		capture.open(0);
	}
	else {
		capture.open("C:\\Home\\Programs\\OpenCV\\project\\openCV_Project\\Ori.mp4");
		 
	}
	if (!capture.isOpened()) { 
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	double fps = capture.get(cv::CAP_PROP_FPS);

	cv::Size size2(
		//320, 240
		(int)capture.get(cv::CAP_PROP_FRAME_WIDTH)/2,
		(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)/2
	);

	cv::VideoWriter writer; 
	writer.open(
		"C:\\Home\\Programs\\OpenCV\\project\\openCV_Project\\OriPyrDOWN.avi"
		, CV_FOURCC('M','P','4','2')
		, 40
		, size2
		, true
	);

	while (true)
	{
		Mat logpolar_frame;
		Mat bgr_frame;

		capture.read(bgr_frame);
 
		if (bgr_frame.empty())
			break;
		imshow("Video_cam", bgr_frame);
		
		pyrDown(bgr_frame, logpolar_frame, Size(
			bgr_frame.cols / 2,
			bgr_frame.rows / 2
		));

		imshow("Video_cam_pyrDown", logpolar_frame);
		writer.write(logpolar_frame);
		
		char c = cv::waitKey(10);

		if (c == 27)
			break;
	}

	capture.release();
	return 0;
}