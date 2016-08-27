#include <qmessagebox.h>
#include <qtextstream.h>
#include <qdebug.h>
#include <qlogging.h>
#include <random>
#include <time.h>

#include <qevent.h>

#include "segmentpaintwidget.h"
#include "hershberger.h"

using std::vector;



QDebug operator<<(QDebug os, const Point& p) //DELETEME
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

QDebug operator<<(QDebug os, const Segment& s) //DELETEME
{
	os << "[" << s.beg << " -> " << s.end << "]";
	return os;
}

SegmentPaintWidget::SegmentPaintWidget(QWidget* obj = 0) : QWidget(obj), segments() {
	segments.push_back(Segment(Point(10, 10), Point(60, 60)));
	segments.push_back(Segment(Point(20, 50), Point(130, 200)));
	segments.push_back(Segment(Point(100, 30), Point(200, 80)));
	srand(time(0));
	this->recalculateEnvelope();
}

void SegmentPaintWidget::paintEvent(QPaintEvent*) {
	QPainter p(this);
	int rad = std::min(this->width() / 2, this->height() / 2);
	p.setPen(QPen(Qt::gray, 1));
	for (int i = 0; i < this->segments.size(); i++){
		if (!segments[i].is_infinite_height()) // Don't draw infinite segments
			p.drawLine(this->segments[i].beg.x, this->segments[i].beg.y, this->segments[i].end.x, this->segments[i].end.y);
	}
	p.setPen(QPen(Qt::darkGreen, 2));
	for (int i = 0; i < this->env.size(); i++){
		if (!env[i].is_infinite_height()) // Don't draw infinite segments
			p.drawLine(this->env[i].beg.x, this->env[i].beg.y, this->env[i].end.x, this->env[i].end.y);
	}
}


void SegmentPaintWidget::clearSegments() {
	qInfo() << "Clear pressed";
	this->segments.clear();
	this->recalculateEnvelope();
}

void SegmentPaintWidget::addRandomSegment() {
	Point p1(rand() % this->width(), rand() % this->height());
	Point p2(rand() % this->width(), rand() % this->height());
	this->segments.push_back(Segment(p1, p2));
	this->recalculateEnvelope();
}

void SegmentPaintWidget::recalculateEnvelope() {
	this->env = lower_envelope_hersh(this->segments);
	this->repaint();
}

void SegmentPaintWidget::mouseDoubleClickEvent(QMouseEvent* evt) {
	QMessageBox(this).show();
}

void SegmentPaintWidget::mousePressEvent(QMouseEvent* evt) {
	if (evt->button() == Qt::MouseButton::RightButton) { // Handle right click
		this->insertedSegment = new Segment(Point(evt->x(), evt->y()), Point(Point::INFINITE_VALUE, Point::INFINITE_VALUE));
	}
	// TODO Handle endpoint dragging
}

void SegmentPaintWidget::mouseReleaseEvent(QMouseEvent* evt) {
	if (evt->button() == Qt::MouseButton::RightButton) {
		// Handle right click release
		this->insertedSegment->end = Point(evt->x(), evt->y());
		Segment s(*this->insertedSegment);
		qInfo() << "Adding segment " << s;
		this->segments.push_back(s);
		delete this->insertedSegment;
		this->recalculateEnvelope();

	}
}