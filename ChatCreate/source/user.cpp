#include "user.h"
int User::UserCount = 1;
User::User()
{
    this ->id = 0;
    this->login = "default";
    this->username = "default";
    this->password = "default";
    this->mail = "default@mail.com";
}

User::User(std::string username, std::string password, std::string mail)
{
    this ->id = UserCount++;
    this->login = username;
    this->username = username;
    this->password = password;
    this->mail = mail;
}

int User::CheckLogin(std::string &_login, std::string &_password) const
{
    if((login == _login) && (_password == password)){
        return -1;
    } else {
        return 0;
    }
}

std::string &User::GetUserName()
{
    return username;
}

int User::GetUserID() const
{
    return id;
}



