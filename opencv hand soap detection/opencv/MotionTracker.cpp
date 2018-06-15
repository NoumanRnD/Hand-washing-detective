#include "stdafx.h"
#include<opencv/cv.h> // all the OpenCV headers, which links to all the libraries

#include<opencv/highgui.h>

#include < opencv2/core/core.hpp>

#include < opencv2/highgui/highgui.hpp>

#include < opencv2/imgproc/imgproc.hpp>

#include < opencv2/opencv.hpp>

#include < opencv2/videoio/videoio.hpp>

using namespace cv; // a &quot;shortcut&quot; for directly using OpenCV functions

class MotionTracker {

private: // private members are accessible/modifiable only inside this class

	// only the functions inside MotionTracker can access/modify the values

	// of these variables

	Mat previousPreviousFrame; // the previous previous frame

	Mat previousFrame; // the previous frame

	Mat currentFrame;

	int xROI; // define the top-left corner of our

	int yROI; // region-of- interest

	int widthROI;

	int heightROI;

	bool firstTime;

	int leftLimit;

	int rightLimit;

	int topLimit;

	int bottomLimit;

public:

	// these member functions can access (read and write) the values

	// of the private attributes

	MotionTracker() { // our constructor; an &quot;initialization&quot;

		xROI = 150; // define the top-left corner of our

		yROI = 150; // region-of- interest

		widthROI = 100;

		heightROI = 100;

		firstTime = true;

	}

	void feedNewframe(Mat frame) {

		Mat diffPrevious; // difference between the previous and current

		 

			Mat grayDiffPrevious;

		int x, y;

		int weight, sumWeight, sumWeightX, sumWeightY;

		int xCenter, yCenter;

		if (firstTime) {

			frame.copyTo(currentFrame);

			frame.copyTo(previousFrame);

			frame.copyTo(previousPreviousFrame);

			firstTime = false;

		}

		previousFrame.copyTo(previousPreviousFrame);

		currentFrame.copyTo(previousFrame);

		frame.copyTo(currentFrame);

		// get the diff between the current frame and the second frame

		 

			absdiff(previousPreviousFrame, frame, diffPrevious);

		// convert the color differences into gray differences

		// now, each pixel is in the range 0..255

		cvtColor(diffPrevious, grayDiffPrevious, CV_BGR2GRAY);

		sumWeightX = sumWeightY = sumWeight = 0; // set them all to zero

		for (y = yROI; y <  yROI + heightROI; y++) { // visit pixels row-by-

			 

				// inside each row, visit pixels from left to right

			for (x = xROI; x <  xROI + widthROI; x++) {

				// weight of the pixel x,y

				weight = grayDiffPrevious.at<unsigned char> (y, x);

				sumWeight = sumWeight + weight;

				sumWeightX = sumWeightX + x * weight;

				sumWeightY += y * weight;

			}

		}

		if (sumWeight != 0) {

			xCenter = sumWeightX / sumWeight;

			yCenter = sumWeightY / sumWeight;

		}

		xROI = xCenter - widthROI / 2; // make the ROI &quot;follow&quot; the

		 

			yROI = yCenter - heightROI / 2;

		// let&#39;s keep the ROI inside the limits at all times

		if (xROI <  leftLimit) { // the ROI is starting to go out on the
 

				xROI = leftLimit; // keep it inside

		}

		if (yROI  < topLimit) { // the ROI is starting to go up out of the
 

				yROI = topLimit; // keep it inside

		}

		if (xROI + widthROI  >= rightLimit) { // ROI starts to go out on the

		 

				xROI = rightLimit - widthROI; // keep it inside

		}

		if (yROI + heightROI >= bottomLimit) { // ROI starts to go out at

			 

				yROI = bottomLimit - heightROI; // keep it inside

		}

	}

	// setROI() is a mutator or &quot;setter&quot; function that is used

	// to modify the values of private attributes

	// This function is like a &quot;guardian&quot; of private information

	void setROI(int new_xROI, int new_yROI, int new_widthROI, int new_heightROI) {

		xROI = new_xROI;

		yROI = new_yROI;

		widthROI = new_widthROI;

		heightROI = new_heightROI;

	}

	void setLimits(int left, int top, int right, int bottom) {

		leftLimit = left;

		rightLimit = right;

		topLimit = top;

		bottomLimit = bottom;

	}

	 	int get_xCenter() { return xROI + widthROI / 2; }

	int get_yCenter() { return yROI + heightROI / 2; }

	int get_widthROI() { return widthROI; }

	int get_heightROI() { return heightROI; }

	void drawROI(Mat frame, Scalar color) {

		rectangle(frame, Rect(xROI, yROI, widthROI, heightROI), color, 2);

	}

}; //