#include "database.h"
#include <memory>

int Database::searchUserByName(std::string username)
{
    auto uit = _usersMapByName.find(username);
    if (uit != _usersMapByName.end()) return uit->second;
  return -1;
}

std::vector<std::string> Database::getUserList() const
{
  std::vector<std::string> userList;
  for(auto user : _usersMapByName)
  {
    userList.push_back(user.first);
  }
  return userList;
}

std::string Database::getUserName(int userId) const
{
  for (auto it = _usersMapByName.begin(); it != _usersMapByName.end(); ++it) {
    if (it->second == userId)
      return it->first;
  }
  return 0;
}

Database::Database() : _users(), _messages()
{
}

int Database::addUser(std::string username, std::string password, std::string mail)
{
    auto uit = _usersMapByName.find(username);
    if (uit != _usersMapByName.end()) return -2;
    User newUser = User(username, password, mail);
    _users.push_back(newUser);
    _usersMapByName.insert({ username, newUser.GetUserID() });
    return newUser.GetUserID();
}

int Database::checkPassword(std::string username, std::string password)
{
    int result = -1;
    for (const auto &u : _users)
    {
        result = u.CheckLogin(username, password);
        if (result != -1) return result;
    }
    return result;
}

void Database::addChatMessage(std::string sender, std::string text)
{
    _messages.push_back(Message(sender, text));
}

bool Database::addPrivateMessage(std::string sender, std::string target, std::string message)
{
    int targetUser = searchUserByName(target);
    if (targetUser < 0)
    {
        return false;
    }
    _messages.push_back(Message(sender, targetUser, message));
    return true;
}

std::vector<std::string> Database::getChatMessages()
{
    std::vector<std::string> strings;
    for (auto &m: _messages)
    {
        if (m.getDestination() == -1)
        {
            strings.push_back("<" + m.getSender() + ">: " + m.getText());
        }
    }
    return strings;
}

std::vector<Message> Database::getPrivateMessage(int userID)
{
    std::vector<Message> strings;
    //int userID = searchUserByName(username);
    for (auto &m : _messages)
    {
    if(userID == -1 && m.getDestination() != -1)
      strings.push_back(m);
    else if(userID != -1 && m.getDestination() == userID)
      strings.push_back(m);
    }
    return strings;
}
