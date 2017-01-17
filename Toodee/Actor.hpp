//
//  Actor.hpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 16/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <stdio.h>
#include <vector>
#include <opencv/cv.h>

class Actor {
private:
    cv::Mat frame; //Not sure is iseful. openCV matrix. Stores the raw image.
    cv::Mat actor; //Actor matrix (extracted foreground)
    std::vector<cv::Point> bkg_pixels, fgd_pixels; //
    int width, height;
    
public:
    Actor();
    Actor(cv::Mat frame);
    int get_width();
    int get_height();
    cv::Vec2i get_size();
    cv::Mat get_frame();
    std::vector<cv::Point> get_background();
    std::vector<cv::Point> get_foreground();
    void add_to_background(cv::Point pixel);
    void add_to_foreground(cv::Point pixel);
    void set_frame(cv::Mat frame);
    void set_width(int width);
    void set_height(int height);
};
#endif /* Actor_hpp */