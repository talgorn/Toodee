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
const int FRAME_WIDTH = 200;
const int FRAME_HEIGHT = 200;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_ACTOR = "ACTOR WINDOW";
const char* btn_actor = "Create actor";
const char* btn_stage = "Create stage";

//App states
enum enum_states
{STATE_VIDEO_FEED, STATE_ACTOR, STATE_STAGE, STATE_SCENE, STATE_QUIT};
enum_states state = STATE_VIDEO_FEED;



//This struct holds mouse data under the tag 'mouse_holder'
typedef struct mouse_data {
    int event;
    int x;
    int y;
    int flags;
} mouse_holder;

//Globals
mouse_holder mouse_data;//Mouse data
bool isActorOK = false;
vector<Actor*> actors_list;
Mat cameraInput;
GrabCut Grab;

//Definitions
void AddActor();
void CreateStage(Mat frame);
void CreateGui();
void ButtonActorCallback(int, void*);
void ButtonStageCallback(int, void*);
void on_mouse_events( int , int , int , int , void* );
void CreateActor();
void showActor(GrabCut &);
//Main func
int main(int argc, const char* argv[]) {
    VideoCapture videoFeed;

    actors_list.clear();
    
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

    CreateGui();
    
    while (1)
    {
        if (videoFeed.read(cameraInput) == false) exit(0);// Exit if no image
        
        switch (state) {
            case STATE_VIDEO_FEED:
                resize(cameraInput, cameraInput,
                       Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
                imshow(WINDOW_MAIN, cameraInput);
                //Show video stream
                waitKey(30);//Window refresh delay
                break;
                
            case STATE_ACTOR:
                {
                    CreateActor();
                }
                break;
                
            case STATE_STAGE:
                break;
                
            case STATE_SCENE:
                break;
                
            case STATE_QUIT:
                break;
        }
    }
    return 0;
}

//Callbacks
void ButtonActorCallback(int, void*)
{
    //Create actor window
    namedWindow(WINDOW_ACTOR, CV_WINDOW_AUTOSIZE);
    //Set the mouse events callback method
    setMouseCallback(WINDOW_ACTOR, on_mouse_events, &mouse_data);
    //initialize GrabCut object with current mframe
    Grab.InitWithImage(cameraInput);
    //Create an Actor object, set image_source as current frame
    AddActor();
    state = STATE_ACTOR;
}

void ButtonStageCallback(int, void*){state = STATE_STAGE;}

void CreateGui()
{
    createButton(btn_stage,ButtonStageCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_actor,ButtonActorCallback,NULL,CV_PUSH_BUTTON,0);
}

void AddActor() {
    static int counter = 0;
    Actor* actor = new Actor();
    //Update actor
    actor->SetImage(Grab.GetSourceImage());
    actor->SetWidth(Grab.GetSourceImage().cols);
    actor->SetHeight(Grab.GetSourceImage().rows);
    
    actor->SetName("Actor_" + to_string(counter++));
    //Push actor in actor list
    actors_list.push_back(actor);
}

///TODO: Selection OK, Refactor for pixel labelings
void CreateActor()
{
    // Select last actor in list
    Actor* actor = actors_list[actors_list.size() -1];
    switch(mouse_data.event)
    {
        case CV_EVENT_MBUTTONDOWN:
            {
            state = STATE_VIDEO_FEED;
            }
            break;
        case EVENT_LBUTTONDOWN:
            {
                //Don't we already have a rectangle set ?
                if(Grab._rectangle_state == GrabCut::NOT_SET)
                {
                    Grab._rectangle_state = GrabCut::IN_PROCESS;
                    Grab._labels_region = Rect( mouse_data.x, mouse_data.y, 1, 1 );
                    cout << "ON FAIT LE RECTANGLE !" << endl;
                }
                //If we do, we are defining bgd / fgd labels for the mask
                if(Grab._rectangle_state == GrabCut::SET)
                {
                    cout << "ON FAIT LES LABELS !" << endl;
                    Grab._labelling_state = GrabCut::IN_PROCESS;
                }
            }
            break;
        case EVENT_MOUSEMOVE:
            {
                if( Grab._rectangle_state == GrabCut::IN_PROCESS )
                {
                    cout << "prit" << endl;
                    Grab._labels_region =
                    Rect( Point(Grab._labels_region.x, Grab._labels_region.y),
                         Point(mouse_data.x, mouse_data.y) );
                }
            }
            break;
        case EVENT_LBUTTONUP:
            {
                if(Grab._rectangle_state == GrabCut::IN_PROCESS)
                {
                    //Define ROI in _mask
                    Grab.SetMaskWithRect();
                    Mat bgdModel;
                    Mat fgdModel;
                    grabCut( Grab.GetSourceImage(), Grab.GetMask(), Grab._labels_region, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT );
                    //Get result from masks & image
                    Mat mask_fgpf = ( Grab.GetMask() == cv::GC_FGD) | ( Grab.GetMask() == cv::GC_PR_FGD);
                    Mat res_img = cv::Mat3b::zeros(Grab.GetSourceImage().rows, Grab.GetSourceImage().cols);
                    Grab.GetSourceImage().copyTo( res_img, mask_fgpf );
                    //imshow("WINDOW_ACTOR", res_img);
                    //waitKey(0);
                    //Grab.GetSourceImage().copyTo( res_img, mask_fgpf );//This should do the trick !!!
                    Grab._rectangle_state = GrabCut::SET;
                    Grab.isMaskInitialized = true;
                    //Met à jour actor
                    actor->SetImage(Grab.GetSourceImage()(Rect(Grab._labels_region)));
                }
            }
            break;
        default:
            break;
    }
    showActor(Grab);
}

void CreateStage(Stage* stage, Mat frame) {
    stage->SetFrame(frame);
    stage->SetWidth(frame.cols);
    stage->SetHeight(frame.rows);
}

void on_mouse_events( int event, int x, int y, int flags, void* ptr){
    //Set mouse data in mouse_data struct
    mouse_data.event = event;
    mouse_data.x = x;
    mouse_data.y = y;
    mouse_data.flags = flags;
}

void showActor(GrabCut &Grab)
{
    if (Grab.GetSourceImage().empty()) return;
    Mat ui_refresh;//Temp image for UI display
    Mat current_mask;//Copy of mask
    
    if(!Grab.isMaskInitialized)
    {
        Grab.GetSourceImage().copyTo(ui_refresh);
    }
    else
    {
        Grab.GetSourceImage().copyTo(ui_refresh);

        /*
        Mat mask = Grab.GetMask();
        Mat bgdModel;
        Mat fgdModel;
        current_mask.create(mask.size(), CV_8UC1 );
        Grab.ProcessMask(mask, current_mask);
        //cv::grabCut(Grab.GetSourceImage(), current_mask, Grab._labels_region, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT );

        current_mask.copyTo(ui_refresh);*/
    }
    
    
    //Draw labels (from vectors: _fgd_pxls, _prob_fgd_pxls, etc)
    
    //If currently defining (MOUSE_MOVE) the initial rectangle, draw it
    if(Grab._rectangle_state == GrabCut::IN_PROCESS)
    {
        rectangle(  ui_refresh,
                  Point( Grab._labels_region.x, Grab._labels_region.y ),
                  Point( Grab._labels_region.x + Grab._labels_region.width,
                        Grab._labels_region.y + Grab._labels_region.height ),
                  GREEN, 1);
    }
    if(Grab._rectangle_state == GrabCut::SET)
        Grab.GetSourceImage().copyTo(ui_refresh);
    imshow(WINDOW_ACTOR, ui_refresh);
    waitKey(30);
}

//cout << "Dans showActor state is: " + to_string(Grab._labelling_state) << endl;




















