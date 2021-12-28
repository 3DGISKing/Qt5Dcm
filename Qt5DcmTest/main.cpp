#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "DcmConverter.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QDir dir("E:/str");

	dir.setNameFilters(QStringList("*.tif"));
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

	QStringList fileList = dir.entryList();

	for (int i = 0; i < fileList.count(); i++)
	{
		QString name = fileList[i];

		QString path = dir.path();

		path = path + "/" + name;
			
		if (!DcmConverter::convert(path)) {
			qDebug() << "failed to convert!";
			return 0;
		}
	}
	
	a.exec();
}
