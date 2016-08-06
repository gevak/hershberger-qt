#ifndef SEGMENTPAINTWIDGET__H_
#define SEGMENTPAINTWIDGET__H_

#include <qwidget.h>
#include <qpainter.h>

#include "segment.h"


class SegmentPaintWidget : public QWidget {
	Q_OBJECT
public:
	std::vector<Segment> segments;
	SegmentPaintWidget(QWidget* obj);
	virtual void paintEvent(QPaintEvent*);
	void clearSegments();
	void SegmentPaintWidget::addRandomSegment();
};

#endif