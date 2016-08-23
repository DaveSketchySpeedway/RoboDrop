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

namespace Ueva
{
	cv::Mat qImage2cvMat(const QImage &qImage);

	QImage cvMat2qImage(const cv::Mat &cvMat);

	void bigPassFilter(std::vector<std::vector< cv::Point_<int> >> &contours, const int &size);

	void trackMarkerIdentities(std::vector<UevaMarker> &newMarkers, std::vector<UevaMarker> &oldMarkers, int &trackTooFar);




	cv::Mat contour2Mask(const std::vector<cv::Point_<int>> &contour, const cv::Size_<int> &sz);

	std::vector<cv::Point_<int>> mask2Contour(const cv::Mat &mask);

	bool isPointInMask(cv::Point_<int> &point, cv::Mat &mask);

	int masksOverlap(cv::Mat &mask1, cv::Mat &mask2);

	int detectKink(std::vector< cv::Point_<int>> &contour, const int &convexSize);

	int detectNeck(std::vector< cv::Point_<int>> &contour, int &kinkIndex, float &neck, const int threshold);

	bool isCombinationPossible(std::vector<int> &combination, std::vector<UevaCtrl> &ctrls);

	void deleteFromCombination(std::vector<int> &combination, const int &value);

	double screen2ctrl(const cv::Point_<int> &point, const int &direction, const double &multiplier);
}
#endif