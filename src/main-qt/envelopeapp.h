#ifndef ENVELOPEAPP_H
#define ENVELOPEAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_envelopeapp.h"
#include "segment.h"
#include <vector>

class EnvelopeApp : public QMainWindow
{
	Q_OBJECT

public:
	EnvelopeApp(QWidget *parent = 0);
	~EnvelopeApp();
	void customUiSetup();

private:
	Ui::EnvelopeAppClass ui;
};

#endif // ENVELOPEAPP_H
