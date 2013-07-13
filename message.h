#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QPointer>

class Message;

typedef QPointer<Message> MessageHandle;

class Message : QObject
{
	Q_OBJECT
public:
	Message(QObject* parent=0);

	QString HandleMessage();
};

#endif // MESSAGE_H
