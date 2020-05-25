#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "trip.hpp"
#include "destination.hpp"
#include "user.hpp"

class Database
{
private:
    User curr_user;
    Vector<Destination> destinations;

public:
    Database();
    //! Register user (if valid and free)
    bool register_user(User user) const;
    //! Get user from users.db by name
    User* get_user_by_username(const char* username) const;
    //! Get user from users.db by email
    User* get_user_by_email(const char* email) const;
    //! Save new user to users.db
    bool add_user(User user) const;

};

#endif // DATABASE_HPP
