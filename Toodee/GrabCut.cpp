
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cv.h>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include "GrabCut.hpp"

using namespace std;
using namespace cv;


GrabCut::GrabCut(const Mat raw_image){
    raw_image_ = raw_image.clone();
    //mask_ = raw_image.clone(); // init pixels mask
}

void GrabCut::extract(Rect actor_zone)
{
    namedWindow("caca", WINDOW_AUTOSIZE);
    Mat result;
    Mat bgd_model, fgd_model; //Used internally by openCV grabcut
    grabCut(raw_image_,
                 mask_,
                 actor_zone,
                 bgd_model,
                 fgd_model,
                 5,
                 GC_INIT_WITH_RECT);
    //result = raw_image_ * mask_;
    Point p1(actor_zone.x, actor_zone.y);
    Point p2(actor_zone.x+200, actor_zone.y+200);
    rectangle(mask_, p1, p2, Scalar(0, 255, 255), 2, 8);
    imshow("caca", mask_);
}

