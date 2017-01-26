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
    this->image_ = NULL;
    this->width_ = 0;
    this->height_ = 0;
}
Actor::Actor(Mat frame)
{
    cvCvtColor(&frame, &image_, CV_8UC3);
    //this->frame_ = frame;
    this->width_ = frame.cols;
    this->height_ = frame.rows;
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
Mat Actor::GetImage() {return image_;}
void Actor::SetImage(Mat frame) {this->image_ = frame;}
void Actor::SetName(string name){this->name_ = name;}
string Actor::GetName() {return this->name_;}
















