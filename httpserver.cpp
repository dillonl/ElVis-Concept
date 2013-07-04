#include <QFile>

#include "httpserver.h"

HttpServer::HttpServer(QObject* parent) : QObject(parent), m_server(NULL)
{
}

HttpServer::~HttpServer()
{
	delete m_server;
}

void HttpServer::start(unsigned short port)
{
	if (m_server == NULL)
	{
		m_port = port;
		m_server = new QHttpServer();
		m_server->listen(QHostAddress::Any, m_port);
		connect(m_server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)), this, SLOT(handle_request(QHttpRequest*,QHttpResponse*)));
	}
}

void HttpServer::stop()
{
	disconnect(m_server, SIGNAL(newRequest(QHttpRequest*,QHttpResponse*)));
	m_server->close();
	m_server->deleteLater();
}

void HttpServer::handle_request(QHttpRequest* request, QHttpResponse* response)
{
	if (request->method() == QHttpRequest::HTTP_GET)
	{
		QString path = request->path();
		path = (QString::compare(path, "/") == 0) ? "/index.html" : path;
		path = "html" + path;

		QString fileString = get_file_string(path);
		if (fileString == NULL)
		{
			response->writeHead(QHttpResponse::STATUS_NOT_FOUND);
			response->end("Requested File Not Found");
		}
		else
		{
			QString contentLength = QString::number(fileString.size());
			response->setHeader("Content-Length", contentLength);
			response->writeHead(200);
			response->write(fileString);
			response->end();
		}
	}
}

QString HttpServer::get_file_string(QString path)
{
	QFile file(path);
	bool ret = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if( ret )
	{
		QTextStream stream(&file);
		return stream.readAll();
	}
	return NULL;
}
