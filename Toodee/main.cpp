//
//  main.cpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 07/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

//Consts
const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_WORK = "Work window";


//A video frame
Mat cameraInput;
Mat workFrame;

int main(int argc, const char* argv[]) {
    //FIRST MAIN BRANCH
    std::cout << "OpenCV Version" << CV_VERSION << std::endl;
    
    //The default video capture feed
    VideoCapture videoFeed;
    
    //Check if camera opens
    if(!videoFeed.isOpened()){
        CV_Assert("Failed to open camera");
    }
    //Set the video feed size
    videoFeed.open(0);//Zero = default camera
    videoFeed.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    videoFeed.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //Create a window to display video stream
    namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_WORK, WINDOW_AUTOSIZE);

    while (1)
    {
        videoFeed.read(cameraInput);
        imshow(WINDOW_MAIN, cameraInput);
        imshow(WINDOW_WORK, cameraInput);
        //Show video stream
        waitKey(30);//Window refresh delay
    }
    return 0;
}
