#include "channelinfowidget.h"

ChannelInfoWidget::ChannelInfoWidget(int id, int numChan, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	oldLabel->setText(QString::number(id));

	for (int i = 0; i < numChan; i++)
	{
		newBox->insertItem(i, QString::number(i));
	}
	newBox->setCurrentIndex(id);

	directionBox->insertItem(0, "^");
	directionBox->insertItem(1, "v");
	directionBox->insertItem(2, "<");
	directionBox->insertItem(3, ">");
	directionBox->setCurrentIndex(0);


}


