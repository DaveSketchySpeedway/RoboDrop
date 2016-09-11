/*
Copyright 2016 David Wong

This file is part of RoboDrop from the uEVA project. https://github.com/DaveSketchySpeedway/uEVA

RoboDrop is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

RoboDrop is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RoboDrop. If not, see <http://www.gnu.org/licenses/>
*/

#include "uevafunctions.h"

cv::Mat Ueva::qImage2cvMat(const QImage &qImage)
{
	// indexed8 to 8uc1 
	//Mat cvMat(qImage.height(), qImage.width(), CV_8UC1,
	//	const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	//return cvMat.clone(); // 1 deep copy otherwise data gone as qImage go out of scope


	// rgb888 to 8uc1
	//Mat color(qImage.height(), qImage.width(), CV_8UC3,
	//	const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	//Mat cvMat;
	//cvtColor(color, cvMat, CV_RGB2GRAY); // deep copy 1
	//return cvMat;

	// argb32 to 8uc1
	cv::Mat color = cv::Mat(qImage.height(), qImage.width(), CV_8UC4,
		const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	cv::Mat cvMat;
	cv::cvtColor(color, cvMat, CV_BGRA2GRAY); // 1 deep copy
	return cvMat;
}

QImage Ueva::cvMat2qImage(const cv::Mat &cvMat)
{
	// 8uc1 to indexed8 
	//static QVector<QRgb> colorTable;
	//if (colorTable.empty())
	//{
	//	for (int i = 0; i < 256; i++)
	//	{
	//		colorTable.push_back(qRgb(i, i, i));
	//	}
	//}
	//QImage qImage(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Indexed8);
	//qImage.setColorTable(colorTable);
	//return qImage; // no need to clone because of qimage implicit sharing

	// rbg8uc3 to rbg888
	QImage qImage = QImage(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB888);
	return qImage; // no deep copy
}

cv::Mat Ueva::contour2Mask(const std::vector< cv::Point_<int> > &contour, const cv::Size_<int> &sz)
{
	std::vector< std::vector< cv::Point_<int> >> contours;
	contours.push_back(contour);
	cv::Mat mask = cv::Mat(sz, CV_8UC1, cv::Scalar_<int>(0));
	cv::drawContours(mask, contours, -1, cv::Scalar_<int>(255), -1);
	return mask;
}

std::vector<cv::Point_<int>> Ueva::mask2Contour(const cv::Mat &mask)
{
	std::vector<std::vector< cv::Point_<int> >> contours;
	cv::findContours(mask, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	return contours[0];
}

void Ueva::bigPassFilter(std::vector<std::vector< cv::Point_<int> >> &contours, const int size)
{
	std::vector<std::vector< cv::Point_<int> >>::iterator iter;
	iter = contours.begin();
	while (iter != contours.end())
	{
		cv::Moments mom = cv::moments(*iter);
		if (mom.m00 < size)
		{
			iter = contours.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void Ueva::trackMarkerIdentities(std::vector<UevaMarker> &newMarkers, std::vector<UevaMarker> &oldMarkers, int trackTooFar)
{
	// distance matrix (each row corresponds to a newMarker)
	std::vector<std::vector<float>> l2NormMatrix;
	for (int i = 0; i < newMarkers.size(); i++)
	{
		std::vector<float> l2NormVector;
		for (int j = 0; j < oldMarkers.size(); j++)
		{
			float l2Norm = sqrt(
				pow(float(newMarkers[i].centroid.x - oldMarkers[j].centroid.x), 2) +
				pow(float(newMarkers[i].centroid.y - oldMarkers[j].centroid.y), 2)
				);
			l2NormVector.push_back(l2Norm);
		}
		l2NormMatrix.push_back(l2NormVector);
	}
	// distance matrix transpose (each row corresponds to an oldMarker)
	std::vector<std::vector<float>> l2NormMatrixT;
	for (int j = 0; j < oldMarkers.size(); j++)
	{
		std::vector<float> l2NormVectorT;
		for (int i = 0; i < newMarkers.size(); i++)
		{
			float l2NormT = l2NormMatrix[i][j];
			l2NormVectorT.push_back(l2NormT);
		}
		l2NormMatrixT.push_back(l2NormVectorT);
	}
	// newMarker assiociates itself with oldMarker
	std::vector<int> newOldIndices;
	if (l2NormMatrixT.size() > 0)
	{
		for (int i = 0; i < l2NormMatrix.size(); i++)
		{
			std::vector<float>::iterator iter = std::min_element(l2NormMatrix[i].begin(), l2NormMatrix[i].end());
			if (*iter <= trackTooFar)
			{
				newOldIndices.push_back(iter - l2NormMatrix[i].begin());
			}
			else
			{
				newOldIndices.push_back(-1);
			}
		}
	}
	// oldMarker associates itself with newMarker
	std::vector<int> oldNewIndices;
	if (l2NormMatrix.size() > 0)
	{
		for (int j = 0; j < l2NormMatrixT.size(); j++)
		{
			std::vector<float>::iterator iter = std::min_element(l2NormMatrixT[j].begin(), l2NormMatrixT[j].end());
			if (*iter <= trackTooFar)
			{
				oldNewIndices.push_back(iter - l2NormMatrixT[j].begin());
			}
			else
			{
				oldNewIndices.push_back(-1);
			}
		}
	}
	// round trip consensus
	for (int i = 0; i < newOldIndices.size(); i++)
	{
		int j = newOldIndices[i];
		if (j > -1)
		{
			int iReturn = oldNewIndices[j];
			if (i == iReturn)
			{
				newMarkers[i].identity = oldMarkers[j].identity;
			}
		}
	}
	// give identity to newly appeared markers
	for (int i = 0; i < newMarkers.size(); i++)
	{
		if (newMarkers[i].identity == -1)
		{
			UevaMarker::counter++;
			newMarkers[i].identity = UevaMarker::counter;
		}
	}
}

int Ueva::detectKink(std::vector< cv::Point_<int>> &contour, const int convexSize)
{
	std::vector<int> hull;
	cv::convexHull(contour, hull);

	std::vector<cv::Vec4i> defects;
	cv::convexityDefects(contour, hull, defects);

	int kinkIndex = -1;
	int depth = 0;
	for (int i = 0; i < defects.size(); i++)
	{
		if (defects[i][2] > defects[i][0] && defects[i][2] < defects[i][1]) // filter opencv bug
		{
			if (defects[i][3] > convexSize * 256) // filter small defects
			{
				if (defects[i][3] > depth) // get deepest defect
				{
					depth = defects[i][3];
					kinkIndex = defects[i][2];
				}
			}
		}
	}

	return kinkIndex;
}

int Ueva::detectNeck(std::vector< cv::Point_<int>> &contour, int &kinkIndex, float &neckDistance, const int threshold)
{
	std::vector<float> profile;
	for (int i = kinkIndex; i < contour.size(); i++)
	{
		float l2Norm = sqrt(
			pow(float(contour[i].x - contour[kinkIndex].x), 2) +
			pow(float(contour[i].y - contour[kinkIndex].y), 2)
			);
		profile.push_back(l2Norm);
		if (UevaDroplet::fileStream.is_open())
		{
			UevaDroplet::fileStream << l2Norm << ",";
		}
	}
	for (int i = 0; i < kinkIndex; i++)
	{
		float l2Norm = sqrt(
			pow(float(contour[i].x - contour[kinkIndex].x), 2) +
			pow(float(contour[i].y - contour[kinkIndex].y), 2)
			);
		profile.push_back(l2Norm);
		if (UevaDroplet::fileStream.is_open())
		{
			UevaDroplet::fileStream << l2Norm << ",";
		}
	}

	p1d::Persistence1D persistence;
	persistence.RunPersistence(profile);

	std::vector< p1d::TPairedExtrema > extremas;
	persistence.GetPairedExtrema(extremas, float(threshold));

	std::vector<int> indices;
	int neckIndex = -1;
	neckDistance = 0.0;
	if (extremas.size() == 2) // 2 maxima droplet is healthy, 1st minima is neck
	{
		sort(extremas.begin(), extremas.end(),
			[](const p1d::TPairedExtrema &a, const p1d::TPairedExtrema &b)
		{
			return a.MinIndex < b.MinIndex;
		});
		for (int i = 0; i < extremas.size(); i++)
		{
			if (extremas[i].MinIndex < (contour.size() - kinkIndex))
			{
				indices.push_back(kinkIndex + extremas[i].MinIndex);
			}
			else
			{
				indices.push_back(extremas[i].MinIndex - (contour.size() - kinkIndex));
			}
		}
		neckIndex = indices[0];
		neckDistance = profile[extremas[0].MinIndex];
	}
	else if (extremas.size() >= 3)  // 3 or more maxima droplet is overgrown, 2nd maxima is neck
	{
		sort(extremas.begin(), extremas.end(),
			[](const p1d::TPairedExtrema &a, const p1d::TPairedExtrema &b)
		{
			return a.MaxIndex < b.MaxIndex;
		});
		for (int i = 0; i < extremas.size(); i++)
		{
			if (extremas[i].MaxIndex < (contour.size() - kinkIndex))
			{
				indices.push_back(kinkIndex + extremas[i].MaxIndex);
			}
			else
			{
				indices.push_back(extremas[1].MaxIndex - (contour.size() - kinkIndex));
			}
		}
		neckIndex = indices[1];
		neckDistance = profile[extremas[1].MaxIndex];
	}

	return neckIndex;
}

int Ueva::masksOverlap(cv::Mat &mask1, cv::Mat &mask2)
{
	cv::Mat mask3 = cv::Mat(mask1.size(), CV_8UC1, cv::Scalar_<int>(0));
	cv::bitwise_and(mask1, mask2, mask3);
	return cv::countNonZero(mask3);
}

bool Ueva::isMarkerInChannel(UevaMarker &marker, UevaChannel &channel, int xMargin, int yMargin)
{
	// channel is vertical
	if (channel.direction <= 1)
	{
		if (marker.centroid.y > (channel.rect.y + yMargin) &&
			marker.centroid.y < (channel.rect.y + channel.rect.height - yMargin))
		{
			uchar*p = channel.mask.ptr<uchar>(marker.centroid.y);
			if (p[marker.centroid.x] > 0)
			{
				return true;
			}
		}
	}
	// channel is horizontal
	if (channel.direction >= 2)
	{
		if (marker.centroid.x >(channel.rect.x + xMargin) &&
			marker.centroid.x < (channel.rect.x + channel.rect.width - xMargin))
		{
			uchar*p = channel.mask.ptr<uchar>(marker.centroid.y);
			if (p[marker.centroid.x] > 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Ueva::isCombinationPossible(std::vector<int> &combination, std::vector<UevaCtrl> &ctrls)
{
	std::sort(combination.begin(), combination.end());
	for (int i = 0; i < ctrls.size(); i++)
	{
		std::vector<int> ctrlOutputIdx;
		for (int j = 0; j < ctrls[i].outputIndices.cols; j++)
		{
			ctrlOutputIdx.push_back(ctrls[i].outputIndices.at<uchar>(j));
		}
		if (combination == ctrlOutputIdx &&	ctrls[i].uncoUnob == 0)
		{
			UevaCtrl::index = i;
			return true;
		}
	}
	return false;
}

void Ueva::deleteFromCombination(std::vector<int> &combination, const int value)
{
	std::vector<int>::iterator iter;
	iter = combination.begin();
	while (iter != combination.end())
	{
		if (*iter == value)
		{
			iter = combination.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

double Ueva::screen2ctrl(const cv::Point_<int> &point, const int &direction, const double &multiplier)
{
	double value;
	switch (direction)
	{
	case 0:
	{
		value = point.y * -1 * multiplier;
		break;
	}
	case 1:
	{
		value = point.y * multiplier;
		break;
	}
	case 2:
	{
		value = point.x * -1 * multiplier;
		break;
	}
	case 3:
	{
		value = point.x * multiplier;
		break;
	}
	}
	return value;
}

double Ueva::neck2ctrl(const float &neckPix, const double &umPerPix, double desire, double thresh, double lowGain, double highGain)
{
	double neckMicron = (double)neckPix * umPerPix;

	double neckNonLinear = 0.0;
	double neckSignal = 0.0;
	if ((neckMicron - desire) > thresh)
	{
		neckNonLinear = neckMicron - (desire + thresh);
		neckSignal = neckNonLinear * highGain;
	}
	else if ((desire - neckMicron) > thresh)
	{
		neckNonLinear = neckMicron - (desire - thresh);
		neckSignal = neckNonLinear * lowGain;
	}

	qDebug() << "non linear: " << neckNonLinear << " signal: " << neckSignal;
	return neckSignal;
}