#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <QHash>
#include <QString>

#include "message.h"

// This enum maps to the enum in /html/scripts/message.js
namespace MessageFactoryEnum
{
enum MessageType
{
	LOAD_PLUGIN = 0,
	LOAD_MODEL = 1
};
}

class MessageFactory
{
public:
	MessageFactory();

	static MessageHandle CreateMessage(QHash<QString, QString> json_map);

private:

};

#endif // MESSAGEFACTORY_H
