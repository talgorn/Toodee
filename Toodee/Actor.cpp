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
    this->frame = NULL;
    this->width = 0;
    this->height = 0;
}
Actor::Actor(Mat frame)
{
    this->frame = frame;
    this->width = frame.cols;
    this->height = frame.rows;
}

//Accessors
int Actor::get_width(){return width;}
int Actor::get_height(){return height;}
void Actor::set_width(int width) {this->width = width;}
void Actor::set_height(int height) {this->height = height;}

Vec2i Actor::get_size(){
    Vec2i size(width, height);
    return size;
}

Mat Actor::get_frame() {return frame;}
void Actor::set_frame(Mat frame) {this->frame = frame;}
vector<Point> Actor::get_background() {return bkg_pixels;}
vector<Point> Actor::get_foreground() {return this->fgd_pixels;}

//Public methods
void Actor::add_to_background(Point pixel_coords) {this->bkg_pixels.push_back(pixel_coords);}
void Actor::add_to_foreground(Point pixel_coords) {this->fgd_pixels.push_back(pixel_coords);}














