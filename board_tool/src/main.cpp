#include <QApplication>
#include "mainform.h"

int main( int argc, char * argv[] )
{
	QApplication a(argc, argv);
	MainForm form;

	form.show();

	return a.exec();
}
