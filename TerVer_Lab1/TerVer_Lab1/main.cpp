#include "terver_lab1.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TerVer_Lab1 w;
	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
	QTextCodec::setCodecForCStrings (codec);
	w.show();
	return a.exec();
}
