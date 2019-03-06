#include "user.h"

User::User(std::string key) :
    key(key)
{

}

std::string User::get_key() const
{
    return key;
}
