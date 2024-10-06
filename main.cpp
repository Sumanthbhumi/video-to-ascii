#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace cv;
using namespace std;

string pixelToAcii(int pixel_intesity) {
	// const string ASCII_CHAR = "@%#*+=-. ";
	const string ASCII_CHAR = " .-+=*#%@";
	// const string ASCII_CHAR = " 1";
	string s = string(1, ASCII_CHAR[pixel_intesity * ASCII_CHAR.length() / 256]);
	return s;
}

int main() {
	string video_path = "/home/bobby/personal/projects/video-to-ascii/vid5.mp4";
	VideoCapture cap(video_path);

	if (!cap.isOpened()) {
		cout << "Error opening file" << endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	cout << fps << endl;

	int fram_duration_ms = 1000 / fps;
	int width = 150;
	int height = 50;

	Mat frame, gray_frame, resized_frame;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
		resize(gray_frame, resized_frame, Size(width, height), 0, 0, INTER_LINEAR);

		string ascii_frame;

		for (int row = 0; row < height; ++row) {
			for (int col = 0; col < width; ++col) {
				ascii_frame += pixelToAcii(resized_frame.at<uchar>(row, col));
			}
			ascii_frame += "\n";
		}

		system("clear");
		cout << ascii_frame;
		this_thread::sleep_for(chrono::milliseconds((int)fps));
	}

	return 0;
}
