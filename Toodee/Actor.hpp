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
    cv::Mat frame_; //Not sure is iseful. openCV matrix. Stores the raw image.
    cv::Mat actor_; //Actor matrix (extracted foreground)
    std::vector<cv::Point> bkg_pixels_, fgd_pixels_; //
    int width_, height_;
    
public:
    Actor();
    Actor(cv::Mat frame);
    int GetWidth();
    int GetHeight();
    cv::Vec2i GetSize();
    cv::Mat GetFrame();
    std::vector<cv::Point> GetBackground();
    std::vector<cv::Point> GetForeground();
    void AddToBackground(cv::Point pixel);
    void AddToForeground(cv::Point pixel);
    void SetFrame(cv::Mat frame);
    void SetWidth(int width);
    void SetHeight(int height);
};
#endif /* Actor_hpp */