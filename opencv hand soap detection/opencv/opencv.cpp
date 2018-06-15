// opencv.cpp : Defines the entry point for the console application.
//

#pragma warning (disable : 4996)
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "stdafx.h"
#include <thread>
#include <vector>
#include "MotionTracker.h"



int main(int argc, char **argv)
{
	MotionTracker mTrack1; // our MotionTracker object is mTrack1

	mTrack1.setROI(10, 20, 150, 150); // set mTrack1&#39;s region-of- interest

	MotionTracker mTrack2; // our MotionTracker object is mTrack1

	mTrack2.setROI(300, 200, 150, 150); // set mTrack1&#39;s region-of- interest

	Mat drawFrame; // where we visualize

	int frameCount; // counts the frames that are read from the camera

	Mat frame; // Mat is a 2-D  matrix  of numbers, containing our image data

	VideoCapture cap(0); // live camera

	if (!cap.isOpened()) { // check if we succeeded in opening the camera

		return -1; // quit the program if we did not succeed

	}

	namedWindow(  "Raw Image"  , CV_WINDOW_NORMAL); // create a window

	namedWindow(  "Draw Frame"  , CV_WINDOW_NORMAL);

	cap  >>   frame;

	mTrack1.setLimits(0, 0, frame.cols / 2, frame.rows);

	mTrack2.setLimits(frame.cols / 2, 0, frame.cols, frame.rows);

	for (frameCount = 0; frame.cols/2 < 100000000; frameCount++) {

		if (frameCount % 100 == 0) { // every 100 frames, print a message

		 printf(" frameCount = %d \n" , frameCount);

		}

		cap  >>   frame; // from the first camera

		flip(frame, frame, 1); // flip the frame horizontally

		imshow(  "Raw Image"  , frame); // display the frame in the window

		mTrack1.feedNewframe(frame);

		mTrack2.feedNewframe(frame);

		frame.copyTo(drawFrame); // create our  drawing  frame

		mTrack1.drawROI(drawFrame, Scalar(0, 0, 255)); // draw mTrack1&#39;s ROI

		mTrack2.drawROI(drawFrame, Scalar(0, 255, 0)); // draw mTrack1&#39;s ROI

		imshow( " Draw Frame"  , drawFrame);

		if (waitKey(20)   == 0) { // wait 20ms and check if a key was

		 

				break; // if a key was pressed, exit the for loop

		}

	}
	
	printf(  "Final frameCount = %d \n"  , frameCount);
	

	return 0;

 
	

}
