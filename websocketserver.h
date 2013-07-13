#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>

#include "qwsserver.h"
#include "qwssocket.h"

class WebSocketServer : public QObject
{
	Q_OBJECT
public:
	WebSocketServer(QObject* parent=0);
	~WebSocketServer();

	void start(unsigned short port);
	void stop();

	QHash<QString, QString> json_to_map(QString json);
	QString map_to_json(QHash<QString, QString> map);

public slots:
	void process_new_connection();
	void process_message(QString message);
	void process_pong(quint64 elapsed_time);
	void socket_disconnected();

private:
	QWsServer* m_server;
	QList<QWsSocket*> m_clients;
};

#endif // WEBSOCKETSERVER_H
