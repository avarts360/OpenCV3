#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
using namespace cv;
using namespace std;

cv::VideoWriter writer;
cv::VideoCapture capture;
int g_slider_position = 0;
int g_run = 1, g_dontset = 0; 
 
void onTrackbarSlide(int pos, void*) {
	writer.set(cv::CAP_PROP_POS_FRAMES, 1);

	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}

int main(int argc, char* argv[]) {
	 
	cv::namedWindow("Video_cam", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Video_cam_pyrDown", cv::WINDOW_AUTOSIZE);


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

	
	writer.open(
		"C:\\Home\\Programs\\OpenCV\\project\\openCV_Project\\OriPyrDOWN.avi"
		, CV_FOURCC('M','P','4','2')
		, 40
		, size2
		, true
	);

	int frames = (int)writer.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int)writer.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)writer.get(cv::CAP_PROP_FRAME_HEIGHT);

	cv::createTrackbar("Position", "Video_cam_pyrDown", &g_slider_position, frames,
		onTrackbarSlide);

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
		
		if (g_run != 0) {
			int current_pos = (int)writer.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Video_cam_pyrDown", current_pos);
			cv::imshow("Video_cam_pyrDown", logpolar_frame);
			g_run -= 1;
		}

		writer.write(logpolar_frame);
		char c = cv::waitKey(10);

		if (c == 's') 
		{
			g_run = 1; cout << "Single step, run = " << g_run << endl;
		}
		if (c == 'r') 
		{
			g_run = -1; cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27)
			break;
	}

	capture.release();
	return 0;
}



