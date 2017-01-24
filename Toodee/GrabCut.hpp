//
//  GrabCut.hpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 18/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//  From openCV GrabCut example:
//  (https://github.com/opencv/opencv/blob/master/samples/cpp/grabcut.cpp)

#ifndef GrabCut_hpp
#define GrabCut_hpp

#include <stdio.h>
#include <string>
#include <opencv/cv.h>

class GrabCut
{
public:
    GrabCut();
    GrabCut(const cv::Mat raw_image);
    void SetRectMask(cv::Rect);
    void SetSourceImage(cv::Mat);
    void Extract(const cv::Rect actor_zone);
    void mouseClick( int event, int x, int y, int flags, void* );
    cv::Mat result_;
private:
    cv::Mat source_image_;
    cv::Mat markers_;
    cv::Mat fg_seed;
    cv::Mat bg_seed;
};
#endif /* GrabCut_hpp */
