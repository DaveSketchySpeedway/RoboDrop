#ifndef UEVAFUNCTIONS_H
#define UEVAFUNCTIONS_H

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <QtGui >
#include <iostream>
#include <fstream>
#include <algorithm>
#include "persistence1d.hpp"

#include "uevastructures.h"

using namespace cv;
using namespace std;

Mat qImage2cvMat(const QImage &qImage);

QImage cvMat2qImage(const Mat &cvMat);

Mat contour2Mask(const vector<Point_<int>> &contour, const Size_<int> &sz);

vector<Point_<int>> mask2Contour(const Mat &mask);

void bigPassFilter(vector<vector< Point_<int> >> &contours, const int &size);

bool isPointInMask(Point_<int> &point, Mat &mask);

int masksOverlap(Mat &mask1, Mat &mask2);

int detectKink(vector< Point_<int>> &contour, const int &convexSize);

int detectNeck(vector< Point_<int>> &contour, int &kinkIndex, float &neck, const int threshold);

bool isCombinationPossible(vector<int> &combination, vector<UevaCtrl> &ctrls);

void deleteFromCombination(vector<int> &combination, const int &value);


#endif