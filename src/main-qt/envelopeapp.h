#ifndef ENVELOPEAPP_H
#define ENVELOPEAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_envelopeapp.h"
#include "segment.h"
#include <vector>

class SegmentPaintWidget : public QWidget {
	Q_OBJECT
public:
	std::vector<Segment> segments;
	SegmentPaintWidget(std::vector<Segment> segments, QWidget* obj);
	virtual void paintEvent(QPaintEvent*);

};

class EnvelopeApp : public QMainWindow
{
	Q_OBJECT

public:
	EnvelopeApp(QWidget *parent = 0);
	~EnvelopeApp();

private:
	Ui::EnvelopeAppClass ui;
};

#endif // ENVELOPEAPP_H
