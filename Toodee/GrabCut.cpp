
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

    if(!_mask.empty()) _mask.setTo(Scalar::all(GC_BGD));
    _fgd_pxls.clear();
    _bgd_pxls.clear();
    _prob_fgd_pxls.clear();
    _prob_bgd_pxls.clear();
    _rectangle_state = NOT_SET;
    _labelling_state = NOT_SET;
}

void GrabCut::SetMaskWithRect(){
    CV_Assert( !_mask.empty() );
    _mask.create(_source_image.rows, _source_image.cols, CV_8UC1);
    _mask.setTo( Scalar(GC_BGD) );//Put all ROI to 0
    //Update ROI with probable fgd pixels defined by user selection
    if(_labels_region.width > 1)
        (_mask(_labels_region)).setTo( Scalar(GC_PR_BGD) );
    else
        cout << "ROI rectangle not defined" << endl;
}


void GrabCut::ProcessMask(Mat &current_mask, Mat &resulting_mask){
    if(current_mask.type() != CV_8UC1)
        CV_Error( Error::StsBadArg,
                 "current mask has incorrect type (not CV_8UC1)." );
    if( resulting_mask.empty() ||
        resulting_mask.rows!=current_mask.rows ||
        resulting_mask.cols!=current_mask.cols )
        resulting_mask.create( resulting_mask.size(), CV_8UC1 );
    
    resulting_mask = current_mask & 1;
    
    Mat bgdModel, fgdModel;
    //cv::grabCut( _source_image,
                //resulting_mask, _labels_region,
                //bgdModel, fgdModel, 4, GC_INIT_WITH_RECT );
    cv::namedWindow("tutu", WINDOW_AUTOSIZE);
    imshow("tutu", resulting_mask);
}

Mat GrabCut::GetMask(){return _mask ;}







