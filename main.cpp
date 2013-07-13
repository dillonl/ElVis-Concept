#include <QApplication>
#include <QDesktopWidget>
#include <QStringList>

#include <iostream>

#include "html5applicationviewer.h"

#include "websocketserver.h"

#include "httpserver.h"

bool REMOTE = true; // ultimately this is not the way I want to keep track of local vs remote

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QStringList argList = QCoreApplication::arguments();

	WebSocketServer socket_server;
	socket_server.start(4849);

	Html5ApplicationViewer viewer;
	if (!argList.contains("-remote")) // only create the viewer if local (not remote)
	{
        REMOTE = false;
		viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
		viewer.showExpanded();
		viewer.loadFile(QLatin1String("html/index.html"));
		viewer.resize(QApplication::desktop()->screen()->rect().width() * .7, QApplication::desktop()->screen()->rect().height() * 0.7); // ensure the application will take up 70% of the screen in both directions
		viewer.move(QApplication::desktop()->screen()->rect().center() - viewer.rect().center()); // this centers our application on the screen
	}
	HttpServer httpServer; // create and start an HTTP server (this is not the WebSocket server)
	httpServer.start(4848);

	return app.exec();
}
