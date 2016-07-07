/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEVA

uEVA is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

uEVA is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with uEva. If not, see <http://www.gnu.org/licenses/>
*/

#include "plotter.h"

Plotter::Plotter(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setWindowFlags(Qt::Window);

	//// 64 RANDOM COLORS
	srand(time(NULL));
	for (int i = 0; i < 64; i++)
	{
		int hue = ((rand() % 8) * 37) % 256;
		int saturation = ((rand() % 8) * 37) % 256;
		colors.push_back(QColor::fromHsv(hue, saturation, 255));
	}

	//// 16 ROTATING PEN STYLES
	for (int i = 0; i < 16; i++)
	{
		int wheel = i % 5 + 1;
		switch (wheel)
		{
		case 1:
			penStyles.push_back(Qt::SolidLine);
			penStyleTexts.push_back("-");
			break;
		case 2:
			penStyles.push_back(Qt::DashLine);
			penStyleTexts.push_back("--");
			break;
		case 3:
			penStyles.push_back(Qt::DotLine);
			penStyleTexts.push_back("...");
			break;
		case 4:
			penStyles.push_back(Qt::DashDotLine);
			penStyleTexts.push_back("-.");
			break;
		case 5:
			penStyles.push_back(Qt::DashDotDotLine);
			penStyleTexts.push_back("-..");
			break;
		}
	}

	//// INITLAIZE TREE
	plotTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
	plotTree->setSelectionBehavior(QAbstractItemView::SelectItems);
	plotTree->setColumnCount(2);
	plotTree->setSortingEnabled(false);
	plotTree->setHeaderLabels(QStringList() <<
		tr("Buffer") <<
		tr("Pen"));
	QTreeWidgetItem *p, *c;
}

Plotter::~Plotter()
{

}

void Plotter::setPlot(const UevaBuffer &b)
{
	//// SYNC TREE WITH BUFFER
	int needToSync = 0;
	QTreeWidgetItem *p, *c;
	if (plotTree->topLevelItemCount() != b.map.size())
	{
		needToSync = 1;
	}
	else
	{
		for (int i = 0; i < plotTree->topLevelItemCount(); i++)
		{
			p = plotTree->topLevelItem(i);
			if (b.map[p->text(0)].size() != p->childCount())
			{
				needToSync = 1;
				break;
			}
		}
	}
	if (needToSync)
	{
		// delete
		while (int itemsLeft = plotTree->topLevelItemCount())
		{
			delete plotTree->takeTopLevelItem(itemsLeft - 1);
		}
		// new
		QMapIterator < QString, QVector<QVector<qreal>> > m(b.map);
		int i = 0;
		while (m.hasNext())
		{
			m.next();
			p = new QTreeWidgetItem(plotTree);
			p->setText(0, m.key());
			for (int j = 0; j < m.value().size(); j++)
			{
				c = new QTreeWidgetItem(p);
				c->setText(0, QString::number(j));
				c->setText(1, penStyleTexts[i]);
				c->setBackgroundColor(1, colors[j]);
			}
			p->setExpanded(true);
			i++;
		}
	}
	
	//// CLEAR PLOT DATA
	plot->clearData();
	plot->clearColors();
	plot->clearPenStyles();

	//// NEW PLOT DATA
	for (int i = 0; i < plotTree->topLevelItemCount(); i++)
	{
		p = plotTree->topLevelItem(i);
		for (int j = 0; j < p->childCount(); j++)
		{
			c = p->child(j);
			if (c->isSelected())
			{
				plot->addData(b.map[p->text(0)][c->text(0).toInt()]);
				plot->addColor(colors[j]);
				plot->addPenStyle(penStyles[i]);
			}
		}
	}

	//// BUFFER INDEX
	plot->setPlotCursor(b.index);
}