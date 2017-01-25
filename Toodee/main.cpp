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
#include "GrabCut.hpp"
#include <string.h>
using namespace std;
using namespace cv;

//Consts
const int FRAME_WIDTH = 600;
const int FRAME_HEIGHT = 600;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_ACTOR = "ACTOR window";
const char* btn_actor = "Create actor";
const char* btn_stage = "Create stage";

//Globals
VideoCapture videoFeed;
Mat cameraInput;
Mat workFrame;
Actor* actor;
Stage* stage;
vector<Actor*> actors_list;
GrabCut Grab; //GrabCut class

//App states
enum enum_states
{STATE_INTRO, STATE_ACTOR, STATE_STAGE, STATE_SCENE, STATE_QUIT};
enum_states state = STATE_INTRO;

//Definitions
void AddActor(Mat frame);
void CreateStage(Mat frame);
void CreateGui();
void ButtonActorCallback(int, void*);
void ButtonStageCallback(int, void*);
void on_mouse( int event, int x, int y, int flags, void* param );
//void on_mouse(int, int, int, int, void*);

//Main func
int main(int argc, const char* argv[]) {
    stage = new Stage();
    actors_list.clear();
    actor = new Actor();

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
    //namedWindow(WINDOW_ACTOR, WINDOW_AUTOSIZE);

    //Create GUI
    CreateGui();
    //setMouseCallback( WINDOW_ACTOR, on_mouse, 0 );
    
    while (1)
    {
        if ( videoFeed.read(cameraInput) == false) exit(0);// Exit if no image
        
        resize(cameraInput, cameraInput,
               Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
        imshow(WINDOW_MAIN, cameraInput);

        switch (state) {
            case STATE_INTRO:
                //printf("Intro...");
                break;
                
            case STATE_ACTOR:
                //Will refactor all this
                {
                AddActor(cameraInput);
                Grab.SetSourceImage(actors_list[0]->GetFrame());
                Rect rect(200, 200, 250, 250);
                Grab.SetRectMask(rect);
                imshow(WINDOW_ACTOR, Grab.result_);
                imshow(WINDOW_MAIN, actors_list[actors_list.size() -1]->GetFrame());
                }
                break;
                
            case STATE_STAGE:
                {
                CreateStage(cameraInput);
                imshow(WINDOW_MAIN, stage->GetFrame());
                }
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
void ButtonActorCallback(int, void*){state = STATE_ACTOR;}
void ButtonStageCallback(int, void*){state = STATE_STAGE;}
/*
void on_mouse( int event, int x, int y, int flags, void* param )
{
    if (STATE_ACTOR == true)
    {
        Grab.mouseClick( event, x, y, flags, param );
    }
}
*/
void CreateGui()
{
    createButton(btn_stage,ButtonStageCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_actor,ButtonActorCallback,NULL,CV_PUSH_BUTTON,0);
}

void AddActor(Mat frame) {
    static int counter = 0;
    //Update GUI
    
    actor->SetFrame(cameraInput);
    actor->SetWidth(cameraInput.cols);
    actor->SetHeight(cameraInput.rows);
    actor->SetName("Actor_" + to_string(counter++));
    actors_list.push_back(actor);
    
    for (int i=0; i < actors_list.size(); i++) {
        cout << "I = " + to_string(i) << endl;
        cout << "nb actors: " + to_string(counter) << endl;
        cout << actors_list[i]->GetName() << endl;
    }
    state = STATE_INTRO;
}

void CreateStage(Mat frame) {
    stage->SetFrame(cameraInput);
    stage->SetWidth(cameraInput.cols);
    stage->SetHeight(cameraInput.rows);
    state = STATE_INTRO;
}

void on_mouse( int event, int x, int y, int flags, void* param )
{
    Grab.mouseClick( event, x, y, flags, param );
}

