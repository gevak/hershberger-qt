#include "segmentpaintwidget.h"
#include <qmessagebox.h>

using std::vector;

SegmentPaintWidget::SegmentPaintWidget(QWidget* obj = 0) : QWidget(obj) {
	vector<Segment> segs;
	segments.push_back(Segment(Point(10, 10), Point(80, 80)));
	segments.push_back(Segment(Point(100, 30), Point(200, 80)));
	this->segments = segs;
}

void SegmentPaintWidget::paintEvent(QPaintEvent*) {
	QPainter p(this);
	int rad = std::min(this->width() / 2, this->height() / 2);
	p.setPen(QPen(Qt::darkGreen, 2));
	for (int i = 0; i < this->segments.size(); i++){
		if (!segments[i].is_infinite_height()) // Don't draw infinite segments
			p.drawLine(this->segments[i].beg.x, this->segments[i].beg.y, this->segments[i].end.x, this->segments[i].end.y);
	}
}
