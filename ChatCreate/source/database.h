#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "message.h"
#include "user.h"
#include <string>
#include <unordered_map>

class Database
{
public:
    std::vector<std::string> getUserList() const;
    std::string getUserName(int userId) const;
    Database();
    int addUser(std::string username, std::string password, std::string mail);
    int checkPassword(std::string username, std::string password);
    void addChatMessage(std::string sender, std::string);
    bool addPrivateMessage(std::string sender, std::string target, std::string message);
    std::vector<std::string> getChatMessages();//показать все сообщения
    std::vector<Message> getPrivateMessage(int userID = -1);

private:
    std::vector<User> _users;
    std::vector<Message> _messages;
    std::unordered_map<std::string, int> _usersMapByName;
    int searchUserByName(std::string);
};

#endif // DATABASE_H
