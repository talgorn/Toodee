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
    this->_frame = NULL;
    this->_width = 0;
    this->_height = 0;
}
Stage::Stage(Mat frame)
{
    this->_frame = frame;
    this->_width = frame.cols;
    this->_height = frame.rows;
}

//Accessors
int Stage::GetWidth(){ return _width; }
int Stage::GetHeight(){ return _height; }
void Stage::SetWidth(int width) { this->_width = width; }
void Stage::SetHeight(int height) { this->_height = height; }

Vec2i Stage::GetSize(){
    Vec2i size(_width, _height);
    return size;
}

Mat Stage::GetFrame() { return _frame; }
void Stage::SetFrame(Mat frame) { this->_frame = frame; }














