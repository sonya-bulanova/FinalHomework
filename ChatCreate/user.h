#ifndef USER_H
#define USER_H

#include <string>
#include "hashpassword.h"

class User
{
public:
    User();
    ~User(){};
    User(std::string username, std::string password, std::string mail);
    int CheckLogin(std::string & _login, std::string & _password) const;
    std::string & GetUserName();
    int GetUserID() const;

private:
    static int UserCount;
    int id;
    std::string login;
    uint * password;
    std::string mail;
    std::string username;
};

#endif // USER_H
