#include <QApplication>
#include <QDesktopWidget>
#include <QStringList>

#include <iostream>

#include "html5applicationviewer.h"

#include "httpserver.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QStringList argList = QCoreApplication::arguments();

	Html5ApplicationViewer viewer;
	if (!argList.contains("-remote")) // only create the viewer if local (not remote)
	{

		viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
		viewer.showExpanded();
		viewer.loadFile(QLatin1String("html/index.html"));
		viewer.resize(QApplication::desktop()->screen()->rect().width() * .7, QApplication::desktop()->screen()->rect().height() * 0.7); // ensure the application will take up 70% of the screen in both directions
		viewer.move(QApplication::desktop()->screen()->rect().center() - viewer.rect().center()); // this centers our application on the screen
	}
	HttpServer server; // create and start a server
	server.start(4848);

	return app.exec();
}
