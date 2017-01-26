
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
    process_mask_ = source_image_.clone();
}

void GrabCut::CreateActor()
{
    //Main loop of grabcut iterations
}

void GrabCut::SetSourceImage(const Mat frame) {
    this->source_image_ = frame.clone();
    this->process_mask_ = Mat(source_image_.rows, source_image_.cols,
                              CV_8UC1);//8bits, 1 channel
    this->process_mask_ = Scalar(GC_BGD);//Init with 0s
    
    actor_state = NOT_SET;
    isMaskInitialized = false;
}

Mat GrabCut::GetSourceImage(){
    return this->source_image_;
}







