#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>

#include "qhttpserver.h"
#include "qhttprequest.h"
#include "qhttpresponse.h"

class HttpServer : QObject
{
	Q_OBJECT
public:
	HttpServer(QObject* parent=0);
	~HttpServer();

	void start(unsigned short port);
	void stop();

signals:

public slots:
	void handle_request(QHttpRequest* request, QHttpResponse* response);

private:
	QString get_file_string(QString path);

	unsigned short m_port;
	QHttpServer* m_server;
};

#endif // HTTPSERVER_H
