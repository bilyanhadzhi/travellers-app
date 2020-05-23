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
    Vector<const User*> friends;
    bool is_valid_username(String username) const;
    bool is_valid_password(String password) const;
    bool is_valid_email(String email) const;
public:
    //! Set new username for user (only if valid and free)
    bool set_username(String username);
    //! Set new password (hash) for user (only if valid)
    bool set_password(String password);
    //! Set new email for user(only if valid)
    bool set_email(String email);
    //! Return whether password matches user's
    bool is_correct_password(const char* password) const;
};

#endif // USER_HPP
