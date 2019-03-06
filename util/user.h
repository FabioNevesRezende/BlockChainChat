#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User
{
public:
    User(std::string key);

    std::string get_key() const;
private:
    std::string key;
};

#endif // USER_H
