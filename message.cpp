#include "message.h"

Message::Message(QObject* parent)
	: QObject(parent)
{
}

QString Message::HandleMessage()
{
	return QString("{\"success\": true}");
}
