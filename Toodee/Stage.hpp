//
//  Scene.hpp
//  Toodee
//
//  Created by Talgorn François-Xavier on 18/01/2017.
//  Copyright © 2017 Talgorn François-Xavier. All rights reserved.
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>
#include <vector>
#include <opencv/cv.h>

class Stage {
private:
    cv::Mat _frame; //Not sure is iseful. openCV matrix. Stores the raw image.
    int _width, _height;
    
public:
    Stage();
    Stage(cv::Mat frame);
    cv::Mat GetFrame();
    int GetWidth();
    int GetHeight();
    cv::Vec2i GetSize();
    void SetFrame(cv::Mat frame);
    void SetWidth(int width);
    void SetHeight(int height);
};
#endif /* Stage_hpp */
