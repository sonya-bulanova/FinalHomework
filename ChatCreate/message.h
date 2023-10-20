#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
public:
    Message();
    Message(std::string writer, std::string text);
    Message(std::string writer, int target, std::string text);

    bool searchByRecipient(int n) const;
    std::string getSender() const;
    int getDestination() const;
    int getID() const;
    std::string getText() const;
private:
    static int num;
    static int messageCounter;
    int id;
    std::string sender;
    int DestinationID;
    std::string text_message;
};

#endif // MESSAGE_H
