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
    User* curr_user;
    Vector<Destination> destinations;
    void copy_from(const Database& other);
    void free_memory();

public:
    Database();
    Database(const Database& other);
    Database& operator=(const Database& other);
    ~Database();
    //! Get user from users.db by name
    User* get_user_by_username(const char* username) const;
    //! Get user from users.db by email
    User* get_user_by_email(const char* email) const;
    //! Save new user to users.db and create personal db file
    bool add_user(User user) const;
    //! Set current user
    bool log_in(const char* username, const char* password);
    //! Get currently logged in user
    User* get_curr_user() const;

};

#endif // DATABASE_HPP
