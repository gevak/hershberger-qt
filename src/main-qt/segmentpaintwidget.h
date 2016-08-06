#ifndef SEGMENTPAINTWIDGET__H_
#define SEGMENTPAINTWIDGET__H_

#include <qwidget.h>
#include <qpainter.h>

#include "segment.h"


class SegmentPaintWidget : public QWidget {
	Q_OBJECT
private:
	Segment* insertedSegment;
public:
	std::vector<Segment> segments;
	std::vector<Segment> env;
	SegmentPaintWidget(QWidget* obj);
	virtual void paintEvent(QPaintEvent*);
	void clearSegments();
	void addRandomSegment();
	void recalculateEnvelope();
	virtual void mouseDoubleClickEvent(QMouseEvent* evt);
	virtual void mousePressEvent(QMouseEvent* evt);
	virtual void mouseReleaseEvent(QMouseEvent* evt);
};

#endif