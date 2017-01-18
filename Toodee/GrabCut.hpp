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

using namespace cv;
using namespace std;

class GCApplication
{
public:
    enum{ NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
    static const int radius = 2;
    static const int thickness = -1;
    
    void reset();
    void setImageAndWinName( const Mat& _image, const string& _winName );
    void showImage() const;
    void mouseClick( int event, int x, int y, int flags, void* param );
    int nextIter();
    int getIterCount() const { return iterCount; }
private:
    void setRectInMask();
    void setLblsInMask( int flags, Point p, bool isPr );
    
    const string* winName;
    const Mat* image;
    Mat mask;
    Mat bgdModel, fgdModel;
    
    uchar rectState, lblsState, prLblsState;
    bool isInitialized;
    
    Rect rect;
    vector<Point> fgdPxls, bgdPxls, prFgdPxls, prBgdPxls;
    int iterCount;
};

#endif /* GrabCut_hpp */
