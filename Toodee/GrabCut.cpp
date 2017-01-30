
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cv.h>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include "GrabCut.hpp"

using namespace std;
using namespace cv;

//Constructors
GrabCut::GrabCut(){
}
GrabCut::GrabCut(const Mat raw_image){
    _source_image = raw_image.clone();
    _mask = _source_image.clone();
}

//
//Public
void GrabCut::InitWithImage(const Mat frame) {
    if( frame.empty() ) return;
    _source_image = frame.clone();
    _mask.create(frame.size(), CV_8UC1);//8bits, 1 channel
    Reset();//Init mask and mask labelling pixels
}

Mat GrabCut::GetSourceImage(){
    return _source_image;
}

//
//Private
void GrabCut::Reset()
{
    if( _mask.empty() ) _mask.setTo(Scalar::all(GC_BGD));
    _fgd_pxls.clear();
    _bgd_pxls.clear();
    _prob_fgd_pxls.clear();
    _prob_bgd_pxls.clear();
    _rectangle_state = NOT_SET;
    _labelling_state = NOT_SET;
}

void GrabCut::SetMaskWithRect(){
    Mat bgdModel, fgdModel;
    CV_Assert( !_mask.empty() );
    _mask.setTo( GC_BGD );//Put all ROI to 0
    _labels_region.x = max(0, _labels_region.x);
    _labels_region.y = max(0, _labels_region.y);
    _labels_region.width = min(_labels_region.width, GetSourceImage().cols-_labels_region.x);
    _labels_region.height = min(_labels_region.height, GetSourceImage().rows-_labels_region.y);
    //Update ROI with probable fgd pixels defined by user selection
    (_mask(_labels_region)).setTo( Scalar(GC_PR_FGD) );

    cv::grabCut( _source_image,
                _mask, _labels_region,
                bgdModel, fgdModel, 5, GC_INIT_WITH_RECT );
    cv::namedWindow("tutu", WINDOW_AUTOSIZE);
    imshow("tutu", _mask);
}


void GrabCut::ProcessMask(Mat &current_mask, Mat &resulting_mask){
    if( current_mask.type()!=CV_8UC1 || resulting_mask.empty())
        CV_Error( Error::StsBadArg,
                 "current maks is empty or has incorrect type (not CV_8UC1)" );
    if( resulting_mask.empty() ||
       resulting_mask.rows!=current_mask.rows ||
       resulting_mask.cols!=current_mask.cols )
        resulting_mask.create( resulting_mask.size(), CV_8UC1 );
    resulting_mask = current_mask & 1;
}

Mat GrabCut::GetMask(){return _mask;};







