#include "uevafunctions.h"

Mat qImage2cvMat(const QImage &qImage)
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
	Mat color = Mat(qImage.height(), qImage.width(), CV_8UC4,
		const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	Mat cvMat;
	cvtColor(color, cvMat, CV_BGRA2GRAY); // 1 deep copy
	return cvMat;
}

QImage cvMat2qImage(const Mat &cvMat)
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

Mat contour2Mask(const vector<Point_<int>> &contour, const Size_<int> &sz)
{
	vector<vector< Point_<int> >> contours;
	contours.push_back(contour);
	Mat mask = Mat(sz, CV_8UC1, Scalar_<int>(0));
	drawContours(mask, contours, -1, Scalar_<int>(255), -1);
	return mask;
}

vector<Point_<int>> mask2Contour(const Mat &mask)
{
	vector<vector< Point_<int> >> contours;
	findContours(mask, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	return contours[0];
}

void bigPassFilter(vector<vector< Point_<int> >> &contours, const int &size)
{
	vector<vector< Point_<int> >>::iterator iter;
	iter = contours.begin();
	while (iter != contours.end())
	{
		Moments mom = moments(*iter);
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

bool isPointInMask(Point_<int> &point, Mat &mask)
{
	uchar *p = mask.ptr<uchar>(point.y);
	if (p[point.x])
		return true;
	return false;
}

int masksOverlap(Mat &mask1, Mat &mask2)
{
	Mat mask3 = Mat(mask1.size(), CV_8UC1, Scalar_<int>(0));
	bitwise_and(mask1, mask2, mask3);
	return countNonZero(mask3);
}

int detectKink(vector< Point_<int>> &contour, const int &convexSize)
{
	vector<int> hull;
	convexHull(contour, hull);

	vector<Vec4i> defects;
	convexityDefects(contour, hull, defects);

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

int detectNeck(vector< Point_<int>> &contour, int &kinkIndex, float &neck, const int threshold)
{
	vector<float> profile;
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

	vector< p1d::TPairedExtrema > extremas;
	persistence.GetPairedExtrema(extremas, float(threshold));

	int neckIndex = -1;
	neck = 0.0;
	if (extremas.size() == 2) // 2 maxima droplet is healthy, 1st minima is neck
	{
		sort(extremas.begin(), extremas.end(),
			[](const p1d::TPairedExtrema &a, const p1d::TPairedExtrema &b)
		{
			return a.MinIndex < b.MinIndex;
		});
		if (extremas[0].MinIndex < (contour.size() - kinkIndex))
		{
			neckIndex = kinkIndex + extremas[0].MinIndex;
		}
		else
		{
			neckIndex = extremas[0].MinIndex - (contour.size() - kinkIndex);
		}
		neck = profile[extremas[0].MinIndex];
	}
	else if (extremas.size() >= 3)  // 3 or more maxima droplet is overgrown, 2nd maxima is neck
	{
		sort(extremas.begin(), extremas.end(),
			[](const p1d::TPairedExtrema &a, const p1d::TPairedExtrema &b)
		{
			return a.MaxIndex < b.MaxIndex;
		});
		if (extremas[1].MaxIndex < (contour.size() - kinkIndex))
		{
			neckIndex = kinkIndex + extremas[0].MaxIndex;
		}
		else
		{
			neckIndex = extremas[1].MaxIndex - (contour.size() - kinkIndex);
		}
		neck = profile[extremas[1].MaxIndex];
	}
	return neckIndex;
}

bool isCombinationPossible(vector<int> &combination, vector<UevaCtrl> &ctrls)
{
	std::sort(combination.begin(), combination.end());
	for (int i = 0; i < ctrls.size(); i++)
	{
		vector<int> ctrlOutputIdx;
		for (int j = 0; j < ctrls[i].outputIdx.cols; j++)
		{
			ctrlOutputIdx.push_back(ctrls[i].outputIdx.at<uchar>(j));
		}
		if (combination == ctrlOutputIdx &&
			ctrls[i].uncoUnob == 0)
		{
			return true;
		}
	}
	return false;
}

void deleteFromCombination(vector<int> &combination, const int &value)
{
	vector<int>::iterator iter;
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