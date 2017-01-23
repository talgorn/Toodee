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

//Constructors
Actor::Actor()
{
    this->frame_ = NULL;
    this->width_ = 0;
    this->height_ = 0;
    bkg_pixels_.clear();
    fgd_pixels_.clear();
}
Actor::Actor(Mat frame)
{
    cvCvtColor(&frame, &frame_, CV_8UC3);
    //this->frame_ = frame;
    this->width_ = frame.cols;
    this->height_ = frame.rows;
    bkg_pixels_.clear();
    fgd_pixels_.clear();
}

//Accessors
int Actor::GetWidth(){return width_;}
int Actor::GetHeight(){return height_;}
void Actor::SetWidth(int width) {this->width_ = width;}
void Actor::SetHeight(int height) {this->height_ = height;}
Vec2i Actor::GetSize(){
    Vec2i size(width_, height_);
    return size;
}
Mat Actor::GetFrame() {return frame_;}
void Actor::SetFrame(Mat frame) {this->frame_ = frame;}
vector<Point> Actor::GetBackground() {return bkg_pixels_;}
vector<Point> Actor::GetForeground() {return this->fgd_pixels_;}
void Actor::SetName(string name){this->name_ = name;}
string Actor::GetName() {return this->name_;}

//Public methods
void Actor::AddToBackground(Point pixel_coords) {this->bkg_pixels_.push_back(pixel_coords);}
void Actor::AddToForeground(Point pixel_coords) {this->fgd_pixels_.push_back(pixel_coords);}














