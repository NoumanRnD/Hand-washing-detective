#pragma once

#pragma warning (disable : 4996)
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "stdafx.h"
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>

#include <opencv2/core/utility.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracker.hpp>

 
using namespace std;
using namespace cv;
class MotionTracker
{
public:
	Mat previousPreviousFrame; // the previous previous frame
	Mat previousFrame; // the previous frame
	Mat currentFrame;

	int xROI; // define the top-left corner of our
	int yROI; // region-of-interest
	int widthROI;
	int heightROI;
	bool firstTime;

	int leftLimit;
	int rightLimit;
	int topLimit;
	int bottomLimit;
	void feedNewframe(Mat frame);
	void  setROI(int new_xROI, int new_yROI, int new_widthROI, int new_heightROI);
	MotionTracker();
	int get_xCenter();
	void drawROI(Mat frame, Scalar color);
	void setLimits(int left, int top, int right, int bottom);
		int get_yCenter();
	int get_widthROI();
	int get_heightROI();
	int start();
	~MotionTracker();
};

