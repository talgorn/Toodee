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
    this->_source_image = NULL;
    this->_width = 0;
    this->_height = 0;
}
Actor::Actor(Mat frame)
{
    cvCvtColor(&frame, &_source_image, CV_8UC3);
    this->_width = frame.cols;
    this->_height = frame.rows;
}

//Accessors
int Actor::GetWidth(){return _width;}
int Actor::GetHeight(){return _height;}
void Actor::SetWidth(int width) {this->_width = width;}
void Actor::SetHeight(int height) {this->_height = height;}
Vec2i Actor::GetSize(){
    Vec2i size(_width, _height);
    return size;
}
Mat Actor::GetImage() {return _source_image;}
void Actor::SetImage(Mat frame) {this->_source_image = frame;}
void Actor::SetName(string name){this->_name = name;}
string Actor::GetName() {return this->_name;}
















