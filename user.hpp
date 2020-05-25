#ifndef USER_HPP
#define USER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "trip.hpp"

class User
{
private:
    String username;
    String email;
    String password_hash;
    Vector<Trip> trips;
    Vector<const User*> friends;
    bool is_valid_password(String password) const;
    bool is_valid_email(String email) const;
    bool is_valid_username(String username) const;
    bool load_trips();
    bool load_friends();
    void set_password_hash(String password_hash);
public:
    User();
    User(String username, String email, String password_hash);
    //! Set new username for user (only if valid and free)
    bool set_username(String username);
    //! Set new email for user(only if valid)
    bool set_email(String email);
    //! Set new password (hash) for user (only if valid)
    bool set_password(String password);
    //! Get username (as String)
    String get_username() const;
    //! Get email (as String)
    String get_email() const;
    //! Get password hash (as String)
    String get_password_hash() const;
    //! Add user information to end of (binary) file
    bool append_to_bin(std::ofstream& of_stream) const;
    //! Return whether password matches user's
    bool is_correct_password(const char* password) const;
};

#endif // USER_HPP
