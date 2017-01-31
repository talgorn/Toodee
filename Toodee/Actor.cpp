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
    _source_image = NULL;
    _image_8CU1 = NULL;
    _width = 0;
    _height = 0;
}
Actor::Actor(Mat frame)
{
    cvCvtColor(&frame, &_source_image, CV_8UC3);
    cvCvtColor(&frame, &_image_8CU1, CV_8UC1);
    this->_width = frame.cols;
    this->_height = frame.rows;
}

//Accessors
int Actor::GetWidth(){return _width;}
int Actor::GetHeight(){return _height;}
void Actor::SetWidth(int width) {_width = width;}
void Actor::SetHeight(int height) {_height = height;}
Vec2i Actor::GetSize(){
    Vec2i size(_width, _height);
    return size;
}
Mat Actor::GetImage() {return _source_image;}
void Actor::SetImage(Mat frame) {_source_image = frame.clone();}
void Actor::SetName(string name){_name = name;}
string Actor::GetName() {return _name;}
















