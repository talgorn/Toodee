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
const cv::Scalar BLUE = cvScalar(255,0,0);
class GrabCut
{
public:
    //Constructors
                GrabCut();
    //Methods
    void        InitWithImage(cv::Mat);
    cv::Mat     GetSourceImage();
    void        SetMaskWithRect();
    void        SetLabelsInMask(cv::Rect);
    void        ProcessMask(cv::Mat &, cv::Mat &);
    cv::Mat     GetMask();

    //Variables
    enum        { NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
    bool        isMaskInitialized;//Either with Rectangle or Labels
    short        _rectangle_state;//STATE_NOT_SET=Updating initial ROI (and mask) with rectangle
    short       _labelling_state;//STATE_NOT_SET=Updating labels of mask
    cv::Rect    _labels_region;//ROI
    std::vector<cv::Point>//mask's labels
    _fgd_pxls, _bgd_pxls,
    _prob_fgd_pxls, _prob_bgd_pxls;//Probable fgd/bgd pixels
private:
    //Methods
    void        Reset();//Init mask and labels
    //Variables
    bool        isMaskInitialised;
    cv::Mat     _source_image;
    cv::Mat     _mask;
};
#endif /* GrabCut_hpp */
