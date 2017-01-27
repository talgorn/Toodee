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
Stage* stage;
vector<Actor*> actors_list;
GrabCut Grab; //GrabCut class

//App states
enum enum_states
{STATE_INTRO, STATE_ACTOR, STATE_STAGE, STATE_SCENE, STATE_QUIT};
enum_states state = STATE_INTRO;

//mouseData
typedef struct mouse_data {
    int event;
    int x;
    int y;
    int flags;
} mouse_holder;//This struct hold mouse data under the tag 'mouse_holder'


//Definitions
void AddActor(Mat frame);
void CreateStage(Mat frame);
void CreateGui();
void ButtonActorCallback(int, void*);
void ButtonStageCallback(int, void*);
void RefreshUI();
void on_mouse_events( int , int , int , int , void* );


//Main func
int main(int argc, const char* argv[]) {
    mouse_holder mouse_data;
    
    stage = new Stage();
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
    //Mouse events callback
    setMouseCallback(WINDOW_MAIN, on_mouse_events, &mouse_data);
    //Create GUI
    CreateGui();
    
    while (1)
    {
        if ( videoFeed.read(cameraInput) == false) exit(0);// Exit if no image
        switch (state) {
            case STATE_INTRO:
                resize(cameraInput, cameraInput,
                       Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
                imshow(WINDOW_MAIN, cameraInput);
                //printf("Intro...");
                break;
                
            case STATE_ACTOR:
                
                //Will refactor all this
                {
                //Grab.CreateActor();
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
void ButtonActorCallback(int, void*)
{
    AddActor(cameraInput);
    Grab.SetSourceImage(actors_list[0]->GetImage());
    state = STATE_ACTOR;
}
void ButtonStageCallback(int, void*){state = STATE_STAGE;}

void CreateGui()
{
    createButton(btn_stage,ButtonStageCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_actor,ButtonActorCallback,NULL,CV_PUSH_BUTTON,0);
}

void AddActor(Mat frame) {
    Actor* actor = new Actor();
    static int counter = 0;
    //Update GUI
    
    actor->SetImage(cameraInput);
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

void on_mouse_events( int event, int x, int y, int flags, void* ptr){
    //Set mouse data in mouse_data struct
    mouse_data* m_data = static_cast<mouse_data*>(ptr);
    m_data->event = event;
    m_data->x = x;
    m_data->y = y;
    m_data->flags = flags;
        
    /*
    cout << "EVT: " + to_string(m_data->event) << endl;
    cout << "X: " + to_string(m_data->x) << endl;
    cout << "Y: " + to_string(m_data->y) << endl;
    cout << "Flag: " + to_string(m_data->flags) << endl;
    */
    
    /*
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
        {
            if (STATE_ACTOR && Grab.actor_state == GrabCut::NOT_SET)
            {
                Grab.actor_state = GrabCut::IN_PROCESS;
                cout << "IN_PROCESS" << endl;
                Grab.actor_region = Rect(x, y, 1, 1);
            }
        }
        case EVENT_MOUSEMOVE:
            if(STATE_ACTOR && Grab.actor_state == GrabCut::IN_PROCESS )
            {
                Grab.actor_region = Rect(Point(Grab.actor_region.x, Grab.actor_region.y),Point(x,y));
                Grab.actor_region.width = x - Grab.actor_region.x;
                Grab.actor_region.height = y - Grab.actor_region.y;
                RefreshUI();
                //refreshUI();
            }
        case EVENT_LBUTTONUP:
            if(STATE_ACTOR && Grab.actor_state == GrabCut::IN_PROCESS )
            {
                //TODO !!!
                /*
                 Mat actor = cameraInput.clone();
                 cameraInput.copyTo(actor(Rect(Grab.actor_region.x, Grab.actor_region.y , Grab.actor_region.x + Grab.actor_region.width, Grab.actor_region.y + Grab.actor_region.height)));
                 imshow("runningUI", actor);


                //refreshUI();
            }
    }
     */
}

void RefreshUI() {
    namedWindow("runningUI", WINDOW_AUTOSIZE);
    
    Mat ui_refresh;
    actors_list[0]->GetImage().copyTo(ui_refresh);//Put source image in ui_refresh mat
    
    if( Grab.actor_state == GrabCut::IN_PROCESS )
    {
        /*
        rectangle( ui_refresh, Point( Grab.actor_region.x, Grab.actor_region.y ), Point(Grab.actor_region.x + Grab.actor_region.width, Grab.actor_region.y + Grab.actor_region.height ), GREEN, 1);*/
        rectangle( ui_refresh, Point( Grab.actor_region.x, Grab.actor_region.y ), Point(Grab.actor_region.x + Grab.actor_region.width, Grab.actor_region.y + Grab.actor_region.height ), GREEN, 1);
    }
    
    imshow(WINDOW_MAIN, ui_refresh);


    waitKey(0);
}








