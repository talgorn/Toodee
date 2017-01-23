
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
    source_image_ = raw_image.clone();
    markers_.setTo((InputArray) source_image_.rows, source_image_.cols);
}


void GrabCut::SetRectMask(Rect sure_fgd) {
    //Set the whole mask as probable background
    markers_ = Mat(source_image_.rows,
                   source_image_.cols,
                   CV_8UC1, GC_PR_BGD);
    
    //Since foreground in include in background
    //We set the background before the foreground
    bg_seed = Mat(source_image_.rows,
                  source_image_.cols,
                  CV_8UC1, GC_BGD);
    
    //Then set the sure foreground
    fg_seed = Mat(sure_fgd.width,
                  sure_fgd.height,
                  CV_8UC1, GC_FGD);
    //Draw roi

    Point p1(sure_fgd.x, sure_fgd.y);
    Point p2(sure_fgd.x+sure_fgd.width, sure_fgd.y+sure_fgd.height);
    rectangle(markers_, p1, p2,
              Scalar(0, 255, 255), 2, 8);
    imshow("marker", markers_);
    
    cv::Mat bgd, fgd;
    //First set the background region
    
    int iterations = 1;
    
    //8bits 3 channels img
    cv::grabCut(source_image_, markers_, sure_fgd, bgd, fgd, iterations, cv::GC_INIT_WITH_RECT);
    
    
    // let's get all foreground and possible foreground pixels
    cv::Mat mask_fgpf = ( markers_ == cv::GC_FGD) | ( markers_ == cv::GC_PR_FGD);
    // and copy all the foreground-pixels to a temporary image
    cv::Mat3b tmp = cv::Mat3b::zeros(source_image_.rows, source_image_.cols);
    source_image_.copyTo(tmp, mask_fgpf);
    // show it
    namedWindow("marker", WINDOW_AUTOSIZE);
    cv::imshow("marker", tmp);
    cv::waitKey(0);
    
}

void GrabCut::Extract(Rect actor_zone)
{
    namedWindow("caca", WINDOW_AUTOSIZE);
    Mat result;
    Mat bgd_model, fgd_model; //Used internally by openCV grabcut
    grabCut(source_image_,
                 markers_,
                 actor_zone,
                 bgd_model,
                 fgd_model,
                 5,
                 GC_INIT_WITH_RECT);
    //result = raw_image_ * mask_;
    Point p1(actor_zone.x, actor_zone.y);
    Point p2(actor_zone.x+200, actor_zone.y+200);
    rectangle(markers_, p1, p2, Scalar(0, 255, 255), 2, 8);
    imshow("caca", markers_);
}

