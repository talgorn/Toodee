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
#include "Stage.hpp"
using namespace std;
using namespace cv;

//Consts
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 380;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_WORK = "Work window";
const char* btn_actor = "Create actor";
const char* btn_stage = "Create stage";

//Globals
VideoCapture videoFeed;
Mat cameraInput;
Mat workFrame;
Actor* actor;
Stage* stage;

//App states
enum enum_states
{STATE_INTRO, STATE_ACTOR, STATE_STAGE, STATE_SCENE, STATE_QUIT};
enum_states state = STATE_INTRO;

//Definitions
void CreateActor(Mat frame);
void CreateStage(Mat frame);
void CreateGui();
void ButtonActorCallback(int, void*);
void ButtonStageCallback(int, void*);

//Main func
int main(int argc, const char* argv[]) {

    actor = new Actor();
    stage = new Stage();
    
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
    CreateGui();

    while (1)
    {
        if ( videoFeed.read(cameraInput) == false) exit(0);// Exit if no image
        
        resize(cameraInput, cameraInput,
               Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
        imshow(WINDOW_WORK, cameraInput);

        switch (state) {
            case STATE_INTRO:
                printf("Intro...");
                break;
                
            case STATE_ACTOR:
                imshow(WINDOW_MAIN, actor->GetFrame());
                break;
                
            case STATE_STAGE:
                imshow(WINDOW_MAIN, stage->GetFrame());
                break;
                
            case STATE_SCENE:
                printf("SCENE...");
                break;
                
            case STATE_QUIT:
                printf("QUIT...");
                break;
        }
        
        //Show video stream
        waitKey(30);//Window refresh delay
    }
    return 0;
}

//Callbacks
void ButtonActorCallback(int, void*)
{
    CreateActor(cameraInput);
    state = STATE_ACTOR;
}
void ButtonStageCallback(int, void*)
{
    CreateStage(cameraInput);
    state = STATE_STAGE;
}

void CreateGui()
{
    createButton(btn_stage,ButtonStageCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_actor,ButtonActorCallback,NULL,CV_PUSH_BUTTON,0);
}

void CreateActor(Mat frame) {
    actor->SetFrame(cameraInput);
    actor->SetWidth(cameraInput.cols);
    actor->SetHeight(cameraInput.rows);
    
    cout << "ACTOR..." << endl;
    cout << actor-> GetHeight() << endl;
    cout << actor-> GetWidth() << endl;
    cout << actor-> GetSize() << endl;
    if(!actor-> GetBackground().empty())
        cout << actor-> GetBackground().at(0) << endl;
    if(!actor-> GetForeground().empty())
        cout << actor-> GetForeground().at(0) <<endl;
}

void CreateStage(Mat frame) {
    stage->SetFrame(cameraInput);
    stage->SetWidth(cameraInput.cols);
    stage->SetHeight(cameraInput.rows);
    
    cout << "ACTOR..." << endl;
    cout << stage-> GetHeight() << endl;
    cout << stage-> GetWidth() << endl;
    cout << stage-> GetSize() << endl;
}
