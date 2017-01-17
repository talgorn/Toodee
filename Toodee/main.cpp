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
#include "Actor.hpp"

using namespace std;
using namespace cv;

//Consts
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 380;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_WORK = "Work window";
const char* btn_actor = "Get actor";

//Globals
Mat cameraInput;
Mat workFrame;
Actor* m_actor;

//Callbacks
void btn_actor_callback(int, void*)
{
    if (m_actor != NULL) {
        m_actor->set_frame(cameraInput);
        m_actor->set_width(cameraInput.cols);
        m_actor->set_height(cameraInput.rows);
        m_actor->add_to_background(Point(0,0));
        m_actor->add_to_foreground(Point(100,100));
        cout << "Allocation done!" << endl;
    }
    cout << "Howdy!" << endl;
}

//Main func
int main(int argc, const char* argv[]) {
    //The default video capture feed
    VideoCapture videoFeed;
    m_actor = new Actor();
    
    //Check if camera opens
    if(!videoFeed.isOpened()){
        CV_Assert("Failed to open camera");
    }
    //Set the video size
    videoFeed.open(0);//Zero = default camera
    videoFeed.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    videoFeed.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //Create a window to display video stream
    namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_WORK, WINDOW_AUTOSIZE);

    //Create GUI
    createButton(btn_actor,btn_actor_callback,NULL,CV_PUSH_BUTTON,0);
    
    while (1)
    {
        videoFeed.read(cameraInput);
        resize(cameraInput, cameraInput,
               Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
        imshow(WINDOW_MAIN, cameraInput);
        if(m_actor->get_height() != 0)
        {
            imshow(WINDOW_WORK, m_actor->get_frame());
            cout << m_actor-> get_height() << endl;
            cout << m_actor-> get_width() << endl;
            cout << m_actor-> get_size() << endl;
            cout << m_actor-> get_background().at(0) << endl;
            cout << m_actor-> get_foreground().at(0) << endl;
        }
        //Show video stream
        waitKey(30);//Window refresh delay
    }
    return 0;
}
