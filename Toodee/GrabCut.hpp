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
    void SetSourceImage(cv::Mat);
    void CreateActor(const cv::Rect actor_zone);
    void mouseClick( int event, int x, int y, int flags, void* );
    cv::Mat clean_actor_;
private:
    void SetRectMask(cv::Rect);
    cv::Mat source_image_;
    cv::Mat process_mask_;
};
#endif /* GrabCut_hpp */
