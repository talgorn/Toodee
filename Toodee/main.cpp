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
#include <vector>

using namespace std;
using namespace cv;

//Consts
const int FRAME_WIDTH = 200;
const int FRAME_HEIGHT = 200;
const string WINDOW_MAIN = "TOODEE";
const string WINDOW_ACTOR = "ACTOR WINDOW";
const char* btn_set_actor = "Set actor";
const char* btn_extract_actor = "Extract actor";
const char* btn_stage = "Create stage";
static const int radius = 5;
static const int thickness = -1;

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
const int BGD_KEY = EVENT_FLAG_SHIFTKEY;
mouse_holder mouse_data;//Mouse data
bool isActorOK = false;
bool isBackground = false;
vector<Actor*> actors_list;
Mat cameraInput;
GrabCut Grab;

bool isFgdLabel = false;//Left click (fgd labels pixels)
bool isBgdLabel = false;//Right click (bgd labels pixles)

//Definitions
void AddActor();
void CreateStage(Mat frame);
void CreateGui();
void ButtonSetActorCallback(int, void*);
void ButtonStageCallback(int, void*);
void on_mouse_events( int , int , int , int , void* );
Mat CreateActor(Mat);

//Main func
int main(int argc, const char* argv[]) {
    VideoCapture videoFeed;
    Mat output_frame;
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
    namedWindow(WINDOW_MAIN, WINDOW_AUTOSIZE | CV_GUI_EXPANDED);
    setMouseCallback(WINDOW_MAIN, on_mouse_events, &mouse_data);
    CreateGui();
    
    while (1)
    {
        if (videoFeed.read(cameraInput) == false) exit(0);// Exit if no image
        
        switch (state) {
            case STATE_VIDEO_FEED:
                cameraInput.copyTo( output_frame );
                //Show video stream
                break;
                
            case STATE_ACTOR:
                {
                    output_frame = CreateActor(cameraInput);
                }
                break;
                
            case STATE_STAGE:
                break;
                
            case STATE_SCENE:
                break;
                
            case STATE_QUIT:
                break;
        }
        //resize(output_frame, output_frame,
        //Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
        if(state == STATE_ACTOR)
        {
            for (int i=0; i < Grab._fgd_pxls.size(); i++)
            {
                Point p = Point(Grab._fgd_pxls.at(i).x , Grab._fgd_pxls.at(i).y);
                circle( output_frame, p, radius, GREEN,  thickness );
                //rectangle(output_frame, Point(Grab._fgd_pxls.at(i).x , Grab._fgd_pxls.at(i).y),
                          //Point(Grab._fgd_pxls.at(i).x+label_size, Grab._fgd_pxls.at(i).y+label_size), GREEN, -1);
            }
            for (int i=0; i < Grab._bgd_pxls.size(); i++)
            {
                Point p = Point(Grab._bgd_pxls.at(i).x , Grab._bgd_pxls.at(i).y);
                circle( output_frame, p, radius, BLUE,  thickness );
                //rectangle(output_frame, Point(Grab._bgd_pxls.at(i).x , Grab._bgd_pxls.at(i).y),
                          //Point(Grab._bgd_pxls.at(i).x+label_size, Grab._bgd_pxls.at(i).y+label_size), BLUE, -1);
            }
        }
        imshow(WINDOW_MAIN, output_frame);
        waitKey(10);
    }
    return 0;
}

//Callbacks
void ButtonSetActorCallback(int, void*)
{
    //initialize GrabCut object with current mframe
    Grab.InitWithImage(cameraInput);
    //Create an Actor object, set image_source as current frame
    AddActor();
    state = STATE_ACTOR;
}

void ButtonExtractActorCallback(int, void*)
{
    //Iterate Grabcut with mask
    cout << "ITERATE GRABCUT WITH MASK !!!" << endl;
    //grabCut( *image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_MASK );
}

void ButtonStageCallback(int, void*){state = STATE_STAGE;}

void CreateGui()
{
    createButton(btn_stage,ButtonStageCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_set_actor,ButtonSetActorCallback,NULL,CV_PUSH_BUTTON,0);
    createButton(btn_extract_actor,ButtonExtractActorCallback,NULL,CV_PUSH_BUTTON,0);
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
Mat CreateActor(Mat frame)
{
    Mat temp_frame;
    actors_list[actors_list.size() -1]->GetImage().copyTo(temp_frame);
    
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
                //Store SHIFT_KEY state -> Yes: isBackground = true;
                isBackground = (mouse_data.flags & BGD_KEY) !=0;
                
                //Don't we already have a rectangle set ?
                if(Grab._rectangle_state == GrabCut::NOT_SET && !isBackground)
                {
                    Grab._rectangle_state = GrabCut::IN_PROCESS;
                    Grab._labels_region = Rect( mouse_data.x, mouse_data.y, 1, 1 );
                }
                //If we do, we are defining bgd / fgd labels for the mask
                if(Grab._rectangle_state == GrabCut::SET)
                {
                    Grab._labelling_state = GrabCut::IN_PROCESS;
                    if(isBackground)
                        {
                        cout << "BACKGROUND LABELS NOW!!!" << endl;
                        }
                    else if(!isBackground)
                        {
                            cout << "FOREGROUND LABELS NOW!!!" << endl;
                        }
                }
            }
            break;
            
        case EVENT_MOUSEMOVE:
            {
                if( Grab._rectangle_state == GrabCut::IN_PROCESS )
                {
                    Grab._labels_region = Rect(Point(Grab._labels_region.x, Grab._labels_region.y),
                                               Point(mouse_data.x, mouse_data.y));
                    Rect( Point(Grab._labels_region.x, Grab._labels_region.y),
                         Point(mouse_data.x, mouse_data.y) );
                    rectangle(temp_frame, Point(Grab._labels_region.x, Grab._labels_region.y),
                              Point(mouse_data.x, mouse_data.y), GREEN, 2);
                } else if (Grab._labelling_state == GrabCut::IN_PROCESS)
                {
                    Point p = Point(mouse_data.x, mouse_data.y);
                    if(!isBackground == true)
                    {
                        cout << "on pushe les FGD labels" << endl;
                        Grab._fgd_pxls.push_back(p);
                        circle( Grab.GetMask(), p, radius, GC_PR_FGD,  thickness );
                    }
                    else if (isBackground == true)
                    {
                        cout << "on pushe les BGD labels" << endl;
                        Grab._bgd_pxls.push_back(Point(mouse_data.x, mouse_data.y));
                        circle( Grab.GetMask(), p, radius, GC_PR_BGD,  thickness );
                    }
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
                    grabCut( Grab.GetSourceImage(), Grab.GetMask(),
                            Grab._labels_region, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT );
                    //Get foreground and probably foreground labelled pixels as a mask
                    Mat mask_fgpf = ( Grab.GetMask() == cv::GC_FGD) | ( Grab.GetMask() == cv::GC_PR_FGD);
                    //Init a zeroed matrix same size as original image
                    Mat res_img = cv::Mat3b::zeros(Grab.GetSourceImage().rows, Grab.GetSourceImage().cols);
                    //Mask original image with  mask_fgpfg, copy the result in res_img
                    Grab.GetSourceImage().copyTo( res_img, mask_fgpf );
                    Grab._rectangle_state = GrabCut::SET;//Done with init rectangle phase
                    Grab.isMaskInitialized = true;//We got a mask
                    //Update actor with resulting masked image
                    actor->SetImage(res_img(Rect(Grab._labels_region)));
                    res_img.copyTo(temp_frame);//The image to be returned to main loop
                    imshow("Actor", actor->GetImage());
                    waitKey(30);
                    Grab._rectangle_state = GrabCut::SET;
                } else if (Grab._labelling_state  == GrabCut::IN_PROCESS)
                {
                    //Set labels in mask
                    Grab._labelling_state  = GrabCut::SET;
                }
            }
            break;
        default:
            break;
    }
    return temp_frame;

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





















