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
    std::string _name;
    cv::Mat     _source_image; //Not sure is iseful. openCV matrix. Stores the raw image.
    cv::Mat     _actor; //Actor matrix (extracted foreground)
    int         _width, _height;
    
public:
    Actor();
    Actor(cv::Mat frame);
    int GetWidth();
    int GetHeight();
    cv::Vec2i   GetSize();
    cv::Mat     GetImage();
    std::vector<cv::Point> GetBackground();
    std::vector<cv::Point> GetForeground();
    void AddToBackground(cv::Point pixel);
    void AddToForeground(cv::Point pixel);
    void SetImage(cv::Mat frame);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetName(std::string name);
    std::string GetName();
};
#endif /* Actor_hpp */