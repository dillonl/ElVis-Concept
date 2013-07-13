#ifndef MAILBOX_H
#define MAILBOX_H

#include "message.h"

extern MessageHandle;

class MailBox
{
public:
    MailBox();

	static void handle_message(MessageHandle message);
};

#endif // MAILBOX_H
