#include "user.h"
#include <cstring>

int User::UserCount = 1;
User::User()
{
    this ->id = 0;
    this->login = "default";
    this->username = "default";
    this->password = 0000;
    this->mail = "default@mail.com";
}

User::User(std::string username, std::string text_password, std::string mail)
{
    this ->id = UserCount++;
    this->login = username;
    this->username = username;
    char* c = strcpy(new char[text_password.length() + 1], text_password.c_str());
    this->password = sha1(c, text_password.size());
    this->mail = mail;
}

int User::CheckLogin(std::string &_login, std::string &_password) const
{
    char* c = strcpy(new char[_password.length() + 1], _password.c_str());
    if((login == _login) && (sha1(c, _password.size()) == password)){
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



