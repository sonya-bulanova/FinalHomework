#include "message.h"

int Message::num = 0;
int Message::messageCounter = 0;

Message::Message()
{
    this->id = num;
    this->sender = "default";
    this->DestinationID = 0;
    this->text_message = "Hello, World!";
}

Message::Message(std::string writer, std::string text)
{
    this->id = num++;
    this->sender = writer;
    this->text_message = text;
    this->DestinationID = -1;
    messageCounter++;
}

Message::Message(std::string writer, int target, std::string text)
{
    this->id = num++;
    this->sender = writer;
    this->text_message = text;
    this->DestinationID = target;
    messageCounter++;
}

bool Message::searchByRecipient(int n) const
{
    return (DestinationID == n);
}

std::string Message::getSender() const
{
    return sender;
}

int Message::getDestination() const
{
    return DestinationID;
}

int Message::getID() const
{
    return id;
}

std::string Message::getText() const
{
    return text_message;
}
