#include "uevafunctions.h"


QImage cvMat2qImage(const Mat &cvMat)
{
	static QVector<QRgb> colorTable;
	if (colorTable.empty())
	{
		for (int i = 0; i < 256; i++)
		{
			colorTable.push_back(qRgb(i, i, i));
		}
	}

	//// CONVERT  (no need to clone as QImage implicit sharing is clever)
	QImage qImage(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Indexed8);
	qImage.setColorTable(colorTable);
	return qImage;
}




Mat qImage2cvMat(const QImage &qImage)
{
	//// CONVERT AND CLONE
	Mat cvMat(qImage.height(), qImage.width(), CV_8UC1,
		const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	return cvMat.clone();
}