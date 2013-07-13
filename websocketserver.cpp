#include <QHash>

#include <iostream>

#include "websocketserver.h"
#include "messagefactory.h"

WebSocketServer::WebSocketServer(QObject* parent)
	: QObject(parent)
{

}

WebSocketServer::~WebSocketServer()
{
	int x = 0;
}

void WebSocketServer::start(unsigned short port)
{
	this->m_server = new QWsServer(this);
	if (!this->m_server->listen(QHostAddress::Any, port))
	{
		std::cout << "An error occurred while starting the server" << std::endl;
	}
	else
	{
		connect(this->m_server, SIGNAL(newConnection()), this, SLOT(process_new_connection()));
	}
}

void WebSocketServer::stop()
{
	this->m_server->close();
}

void WebSocketServer::process_new_connection()
{
	QWsSocket* client_socket = m_server->nextPendingConnection();

	connect(client_socket, SIGNAL(frameReceived(QString)), this, SLOT(process_message(QString)));
	connect(client_socket, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
	connect(client_socket, SIGNAL(pong(quint64)), this, SLOT(process_pong(quint64)));

	this->m_clients << client_socket;
}

void WebSocketServer::process_message(QString json_string)
{
	QWsSocket* socket = qobject_cast<QWsSocket*>(sender());
	if (socket == NULL)
	{
		return;
	}

	QHash<QString, QString> json_map = json_to_map(json_string);
	MessageHandle message = MessageFactory::CreateMessage(json_map);
	QString response = message->HandleMessage();
	// Here is where we invoke the mailbox and messaging system
	socket->write(response);
}

void WebSocketServer::process_pong(quint64 elapsed_time)
{

}

void WebSocketServer::socket_disconnected()
{
	QWsSocket* socket = qobject_cast<QWsSocket*>(sender());
	if (socket == NULL)
	{
		return;
	}
	this->m_clients.removeOne(socket);
	socket->deleteLater();
}

//TODO: complete this function
//This function converts a json string to a QHash
QHash<QString, QString> WebSocketServer::json_to_map(QString json)
{
	QHash<QString, QString> map;
	return map;
}

//TODO: complete this function
//This function converts a QHash to a json string
QString WebSocketServer::map_to_json(QHash<QString, QString> map)
{
	QString json = "";
	return json;
}
