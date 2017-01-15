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
const int FRAME_WIDTH = 1024;
const int FRAME_HEIGHT = 768;
const string WINDOW_ORIGINAL_NAME = "Camera input";
const string WINDOW_BKG_NAME = "Background";
const string WINDOW_ACTOR_NAME = "Actor";
const string WINDOW_DIFF_NAME = "Diff";


//A video frame
Mat cameraInput;
Mat bkgFrame, greyBkg;
Mat actorFrame, greyAct;
Mat diffFrame, greyDiff;

int H_MIN = 256;
int H_MAX = 256;

//Callbacks to tracbars
const String trackbarWindowName = "Trackbars";
void on_trackbar_min( int value, void*)
{//This function gets called whenever a
    // trackbar position is changed
    
    string out_value = "HMIN = " + to_string(value);
    cout << out_value << endl;
}
void on_trackbar_max( int value, void*)
{//This function gets called whenever a
    // trackbar position is changed
    string out_value = "HMAX = " + to_string(value);
    cout << out_value << endl;
}

void createTrackbars(){
    //create window for trackbars
    namedWindow(trackbarWindowName,
                CV_WINDOW_NORMAL |
                CV_WINDOW_KEEPRATIO |
                CV_GUI_EXPANDED);
    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar_min );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar_max );
    
    //createButton(sceneButton, on_scene_button);
}


int main(int argc, const char* argv[]) {
    //FIRST MAIN BRANCH
    std::cout << "OpenCV Version" << CV_VERSION << std::endl;
    createTrackbars();
    
    int tresh = 15;
    
    //The video capture feed
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
    namedWindow(WINDOW_ORIGINAL_NAME, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_ACTOR_NAME, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_ACTOR_NAME, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_DIFF_NAME, WINDOW_AUTOSIZE);

    videoFeed.read(cameraInput);
    diffFrame = cameraInput;
    cvtColor(diffFrame, greyDiff, CV_BGR2GRAY);
    
    bkgFrame = cameraInput;
    //cvtColor(bkgFrame, greyBkg, CV_32FC1);
    cvtColor(bkgFrame, greyBkg, CV_BGR2GRAY);
    while (1)
    {
        videoFeed.read(cameraInput);
        imshow(WINDOW_ORIGINAL_NAME, cameraInput);
        //Extract bkg
        imshow(WINDOW_BKG_NAME, greyBkg);
        
        //Extract actor
        actorFrame = cameraInput;
        cvtColor(actorFrame, greyAct, CV_BGR2GRAY);
        imshow(WINDOW_ACTOR_NAME, greyAct);
        
        //cout << greyAct.rows << endl;
        //cout << greyAct.cols << endl;

        for (int r=0; r < greyAct.rows; r++)
            for (int c=0; c < greyAct.cols; c++)
            {
                //cout << "BKG ";
                //cout << greyBkg.at<char>(r,c) << endl;
                //cout << "ACT "; cout << greyAct.at<char>(r,c) << endl;
                //cout << abs( greyAct.at<char>(r,c) - greyBkg.at<char>(r,c) ) << endl;
                if( abs( greyAct.at<char>(r,c) - greyBkg.at<char>(r,c) ) <= tresh )
                {
                    //cout << abs( greyAct.at<char>(r,c) - greyBkg.at<char>(r,c) ) << endl;
                    //cout << r <<"SET TO ZERO!" << endl;
                    greyDiff.at<char>(r,c) = 0;
                }
                else greyDiff.at<char>(r,c) = greyAct.at<char>(r,c);
            }
        //threshold(greyDiff, greyDiff, 80, 80, 3);
        imshow(WINDOW_DIFF_NAME, greyDiff);
        //Show video stream
        waitKey(60);//Window refresh delay
    }
    return 0;
}
