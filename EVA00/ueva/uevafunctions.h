#ifndef UEVAFUNCTIONS_H
#define UEVAFUNCTIONS_H

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <QtGui >

using namespace std;
using namespace cv;

QImage cvMat2qImage(Mat &cvMat);

Mat qImage2cvMat(QImage &qImage);



#endif