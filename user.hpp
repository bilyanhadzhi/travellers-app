#ifndef USER_HPP
#define USER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "trip.hpp"

class User
{
private:
    String username;
    String password_hash;
    String email;
    Vector<Trip> trips;
    Vector<User*> friends;

public:
};

#endif // USER_HPP
