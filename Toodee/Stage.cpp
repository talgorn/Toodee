//
//  Stage.cpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 16/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//
#include <vector>
#include <opencv/cv.h>
#include "Stage.hpp"

using namespace cv;
using namespace std;

//CONSTS

//Constructors
Stage::Stage()
{
    this->frame_ = NULL;
    this->width_ = 0;
    this->height_ = 0;
}
Stage::Stage(Mat frame)
{
    this->frame_ = frame;
    this->width_ = frame.cols;
    this->height_ = frame.rows;
}

//Accessors
int Stage::GetWidth(){ return width_; }
int Stage::GetHeight(){ return height_; }
void Stage::SetWidth(int width) { this->width_ = width; }
void Stage::SetHeight(int height) { this->height_ = height; }

Vec2i Stage::GetSize(){
    Vec2i size(width_, height_);
    return size;
}

Mat Stage::GetFrame() { return frame_; }
void Stage::SetFrame(Mat frame) { this->frame_ = frame; }














