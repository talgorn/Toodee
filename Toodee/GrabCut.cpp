
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









