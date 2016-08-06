
#include <vector>

#include <QPushButton>
#include <qboxlayout.h>
#include <qpainter.h>

#include "envelopeapp.h"
#include "segment.h"
#include "segmentpaintwidget.h"

using std::vector;

EnvelopeApp::EnvelopeApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->customUiSetup();
}

void EnvelopeApp::customUiSetup() {
	SegmentPaintWidget* drawWidget = new SegmentPaintWidget(this->centralWidget());
	drawWidget->setGeometry(0, 0, 300, 300);
	this->ui.centralWidget = drawWidget;
	this->setWindowTitle("Envelope Display");
}

EnvelopeApp::~EnvelopeApp()
{

}