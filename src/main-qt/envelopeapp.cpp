
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
	this->setWindowTitle("Envelope Display");
}

EnvelopeApp::~EnvelopeApp()
{

}