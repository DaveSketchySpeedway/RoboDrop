#ifndef UEVAFUNCTIONS_H
#define UEVAFUNCTIONS_H

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <QtGui >
#include <iostream>

using namespace std;
using namespace cv;

Mat qImage2cvMat(const QImage &qImage);

QImage cvMat2qImage(const Mat &cvMat);

void bigPassFilter(vector<vector< Point_<int> >> &contours, const int &size);

bool isPointInMask(Point_<int> &point, Mat &mask);



#endif