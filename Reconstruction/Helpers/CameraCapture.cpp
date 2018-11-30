#include "stdafx.h"
#include "CameraCapture.h"

namespace Helpers {
	CameraCapture::CameraCapture()
	{
	}

	CameraCapture::~CameraCapture()
	{
	}

	bool CameraCapture::Visualize(bool showGrid)
	{
		try
		{
			// open cameras
			VideoCapture principalCamera(0); 
			VideoCapture secondaryCamera(1);

			Point p1;
			Point p2;

			// check if Principal Camera is opened
			if (!principalCamera.isOpened()) {
				throw exception("Error when Principal Camera was opened");
			}

			// check if Secundary Camera is opened
			if (!secondaryCamera.isOpened()) {
				throw exception("Error when Secondary Camera was opened");
			}

			namedWindow("Principal Camera", 1);
			namedWindow("Secondary Camera", 1);

			cout << "Press any key to stop..." << endl;

			for (;;)
			{
				Mat principalFrame, secondaryFrame;

				// get a new frame from camera
				principalCamera >> principalFrame;
				secondaryCamera >> secondaryFrame; 

				// Tag the frames
				cv::putText(principalFrame, "Principal Camera", Point(40, 40), 1, 5, Scalar(255, 0, 0));
				cv::putText(secondaryFrame, "Secondary Camera", Point(40, 40), 1, 5, Scalar(255, 0, 0));

				// Show Grid
				if (showGrid) {
					line(principalFrame, Point(340, 0), Point(340, 480), Scalar(0), 3);
					line(principalFrame, Point(0, 240), Point(680, 240), Scalar(0), 3);

					line(secondaryFrame, Point(340, 0), Point(340, 480), Scalar(0), 3);
					line(secondaryFrame, Point(0, 240), Point(680, 240), Scalar(0), 3);
				}

				// Show Frames
				imshow("PrincipalCamera", principalFrame);
				imshow("SecondaryCamera", secondaryFrame);
			
				// Press any key to exit
				if (waitKey(30) >= 0) break;

				p1.x = 320;
				p1.y = 0;
				p2.x = 320;
				p2.y = 480;

				line(principalFrame, p2, p1, Scalar(255, 0, 0), 2, 8);
			}
			// the camera will be deinitialized automatically in VideoCapture destructor

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Camera Capture: " << ex.what() << endl;
			return false;
		}		
	}

	bool CameraCapture::Capture(string pathExport, bool showGrid, bool exportGrid)
	{
		try
		{
			// open cameras
			VideoCapture principalCamera(0); 
			VideoCapture secundaryCamera(1);

			// Points to grid
			Point p1;
			Point p2;

			// Frames to manage
			Mat principalFrame, secondaryFrame;
			Mat auxPrincipalFrame, auxSecondaryFrame;

			// check if Principal Camera is opened
			if (!principalCamera.isOpened()) {
				throw exception("Error when Principal Camera was opened");
			}
			
			// check if Secundary Camera is opened
			if (!secundaryCamera.isOpened()) {
				throw exception("Error when Secondary Camera was opened");
			}

			namedWindow("Principal Camera", 1);
			namedWindow("Secondary Camera", 1);

			// get a new frame from camera
			principalCamera >> principalFrame; 
			secundaryCamera >> secondaryFrame;

			// Check if need to export the grid
			if (!exportGrid) {
				principalFrame.copyTo(auxPrincipalFrame);
				secondaryFrame.copyTo(auxSecondaryFrame);
			}

			// Show Grid
			if (showGrid) {
				line(principalFrame, Point(340, 0), Point(340, 480), Scalar(0), 3);
				line(principalFrame, Point(0, 240), Point(680, 240), Scalar(0), 3);

				line(secondaryFrame, Point(340, 0), Point(340, 480), Scalar(0), 3);
				line(secondaryFrame, Point(0, 240), Point(680, 240), Scalar(0), 3);
			}

			// Show frames
			imshow("SecondaryFrame", secondaryFrame);
			imshow("PrincipalFrame", principalFrame);

			// Export frames
			if (!exportGrid) {
				imwrite(pathExport + "\\principalFrame.png", principalFrame);
				imwrite(pathExport + "\\secondaryFrame.png", secondaryFrame);
			}
			else {
				imwrite(pathExport + "\\principalFrame.png", auxPrincipalFrame);
				imwrite(pathExport + "\\secondaryFrame.png", auxSecondaryFrame);
			}			

			p1.x = 320;
			p1.y = 0;
			p2.x = 320;
			p2.y = 480;
			line(principalFrame, p2, p1, Scalar(255, 0, 0), 2, 8);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Camera Capture: " << ex.what() << endl;
			return false;
		}
	}
}