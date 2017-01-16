//
//  Actor.cpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 16/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//
#include <vector>
#include "Actor.hpp"
#include <opencv/cv.h>

using namespace cv;
using namespace std;

//CONSTS
const short MAX_UNDO = 10;

class Actor {
private:
    cv::Mat raw_data; //Not sure is iseful. openCV matrix. Stores the raw image.
    cv::Mat actor; //Actor matrix (extracted foreground)
    vector<Point> *bkg_pixels, *fgd_pixels; //
    int actor_width, actor_height;
    
public:
    Actor(Mat frame);
    int get_width();
    int get_height();
    vector<Point>* get_background();
    vector<Point>* get_foreground();
};

//Constructor
Actor::Actor(Mat frame)
{
    raw_data = frame;
}
//Accessors
int Actor::get_width()
{
    return actor_width;
}
int Actor::get_height()
{
    return actor_height;
}
vector<Point>* Actor::get_background()
{
    return bkg_pixels;
}
vector<Point>* Actor::get_foreground()
{
    return bkg_pixels;
}



















