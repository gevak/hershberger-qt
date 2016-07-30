#include "segment.h"
#include "envelopeapp.h"

#include <QApplication>
#include <QPushButton>
#include <qboxlayout.h>
#include <qpainter.h>

using std::vector;

SegmentPaintWidget::SegmentPaintWidget(vector<Segment> segments, QWidget* obj = 0) : QWidget(obj) {
	this->segments = segments;
}

void SegmentPaintWidget::paintEvent(QPaintEvent*) {
	QPainter p(this);
	int rad = std::min(this->width() / 2, this->height() / 2);
	p.setPen(QPen(Qt::darkGreen, 2));
	for (int i = 0; i <  this->segments.size(); i++){
		if (!segments[i].is_infinite_height()) // Don't draw infinite segments
			p.drawLine(this->segments[i].beg.x, this->segments[i].beg.y, this->segments[i].end.x, this->segments[i].end.y);
	}
}


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	EnvelopeApp w;
	vector<Segment> segments;
	segments.push_back(Segment(Point(10, 10), Point(80, 80)));
	segments.push_back(Segment(Point(100, 30), Point(200, 80)));
	QWidget *container = new SegmentPaintWidget(segments, &w);
	QPushButton* okButton = new QPushButton("OK");
	QPushButton* cancelButton = new QPushButton("Cancel");

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addStretch(1);
	hbox->addWidget(okButton);
	hbox->addWidget(cancelButton);

	QVBoxLayout* vbox = new QVBoxLayout();
	vbox->addStretch(1);
	vbox->addLayout(hbox);

	container->setLayout(vbox);
	container->setGeometry(0, 0, 300, 300);

	QPainter paint(container);
	paint.begin(container);
	paint.setPen(QPen(Qt::black, 5));
	paint.drawLine(10, 10, 80, 80);
	paint.end();

	w.setCentralWidget(container);
	w.setWindowTitle("Envelope Display");
	w.show();
	return app.exec();
}
