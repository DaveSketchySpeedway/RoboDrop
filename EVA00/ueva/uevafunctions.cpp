#include "uevafunctions.h"


QImage cvMat2qImage(Mat &cvMat)
{
	//// CONVERT  (no need to clone as QImage implicit sharing is clever)
	QImage qImage = QImage(0, 0, QImage::Format_Indexed8);


	return qImage;
}




Mat qImage2cvMat(QImage &qImage)
{
	//// CLONE AND CONVERT
	Mat cvMat = Mat(0, 0, CV_8UC1);




	return cvMat;
}