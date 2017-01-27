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

//Const
const cv::Scalar GREEN = cvScalar(0,255,0);

class GrabCut
{
public:
    //Constructors
    GrabCut();
    GrabCut(const cv::Mat raw_image);
    //Methods
    void SetSourceImage(cv::Mat);
    cv::Mat GetSourceImage();
    //Variables
    enum{ NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
    bool isMaskInitialized;
    cv::Mat clean_actor_;
    bool actor_state;
    cv::Rect actor_region;
private:
    void SetRectMask(cv::Rect);
    cv::Mat source_image_;
    cv::Mat process_mask_;
};
#endif /* GrabCut_hpp */
