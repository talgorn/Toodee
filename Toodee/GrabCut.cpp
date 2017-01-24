
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cv.h>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include "GrabCut.hpp"

using namespace std;
using namespace cv;

GrabCut::GrabCut(){
}

GrabCut::GrabCut(const Mat raw_image){
    source_image_ = raw_image.clone();
    markers_.setTo((InputArray) source_image_.rows, source_image_.cols);
}

void GrabCut::SetSourceImage(Mat frame) {
    this->source_image_ = frame;
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

    cv::Mat bgd, fgd;//Used internally by openCV grabCut()
    int iterations = 1;
    cv::grabCut(source_image_, markers_,
                sure_fgd,
                bgd, fgd,
                iterations, cv::GC_INIT_WITH_RECT);
        
    // let's get all foreground and possible foreground pixels
    cv::Mat mask_fgpf = ( markers_ == cv::GC_PR_FGD) | ( markers_ == cv::GC_PR_FGD);
    // and copy all the foreground-pixels to a temporary image
    result_ = cv::Mat3b::zeros(source_image_.rows, source_image_.cols);
    source_image_.copyTo(result_, mask_fgpf);
}

void GrabCut::Extract(Rect actor_zone)
{
    Mat result;
    Mat bgd_model, fgd_model; //Used internally by openCV grabcut
    grabCut(source_image_,
                 markers_,
                 actor_zone,
                 bgd_model,
                 fgd_model,
                 5,
                 GC_INIT_WITH_RECT);
}


void GrabCut::mouseClick( int event, int x, int y, int flags, void* ){
    cout << "Mouse EVT" << endl;
}


