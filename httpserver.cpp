#include <QFile>

#include <iostream>

#include "httpserver.h"

#include "glwidget.h"

extern bool REMOTE;

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

        if (path.startsWith("/message/")) // this is a json request and not a file request, I'll probably replace this code with websockets
		{
            // whether we use regular http or websockets we'll implement a message handling class that uses signals and slots to update the UI
			QString jsonResponse = QString("{\"startWebGL\": \"true\", \"value\": \"7\"}");
			QString contentLength = QString::number(jsonResponse.size());
			response->setHeader("content-type", "application/json; charset=utf-8");
			response->setHeader("Content-Length", contentLength);
			response->setHeader("version", "HTTP/1.1");
			response->setHeader("Date", "Thu, 04 Jul 2013 11:39:30 GMT");
			response->writeHead(200);
			response->write(jsonResponse);

			response->end();

            if (!REMOTE)
            {
                GLWidget* widget = new GLWidget();
                widget->show();
            }
		}
		else
		{
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
}

QString HttpServer::get_file_string(QString path)
{
    QString pwd("");
    char * PWD;
    PWD = getenv ("PWD");
    pwd.append(PWD);
    // in windows the relative path works fine but I still have to use this hack for osx

    QFile file(pwd.toStdString() + path);
	bool ret = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if( ret )
	{
		QTextStream stream(&file);
		return stream.readAll();
	}
	return NULL;
}
