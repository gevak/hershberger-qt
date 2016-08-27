#include "segment.h"
#include "envelopeapp.h"

#include <QApplication>


using std::vector;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	EnvelopeApp w;
	w.show();
	return app.exec();
}
