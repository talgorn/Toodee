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
    GrabCut(const cv::Mat raw_image);
    void extract(const cv::Rect actor_zone);
private:
    cv::Mat raw_image_;
    cv::Mat mask_;
};

#endif /* GrabCut_hpp */
