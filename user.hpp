#ifndef USER_HPP
#define USER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "trip.hpp"

//! The user class, which stores its username, email, password hash(!), trips and friends
/*!
    Trips are loaded from the 'personal database' of the user, i.e. the file with the same
    name at path db/users/

    Friends are not stored as user pointers, but instead as simply their usernames,
    in order to keep the personal database of the user lean.
    It is Database's responsibility to load users from files, all
    a user knows about his friends are their usernames.

    The passwords are hashed via bcrypt and stored as such.
*/

class User
{
private:
    String username;
    String email;
    String password_hash;
    Vector<Trip> trips;
    Vector<String> friends_usernames;
    bool is_valid_password(String password) const;
    bool is_valid_email(String email) const;
    bool is_valid_username(String username) const;
    void set_password_hash(String password_hash);
public:
    //! Create an all-empty user (for array purposes)
    User();
    //! Create new user
    User(String username, String email, String password_hash);
    //! Set username for user (only if valid and free)
    bool set_username(String username);
    //! Set email for user (only if valid)
    bool set_email(String email);
    //! Set password (hash) for user (only if valid)
    bool set_password(String password);
    //! Get username
    String get_username() const;
    //! Get email
    String get_email() const;
    //! Get password hash
    String get_password_hash() const;
    //! Get copy of usernames of user's friends
    Vector<String> get_friends_usernames() const;
    //! Get copy of trips for user
    Vector<Trip> get_trips() const;
    //! Append user username, email, and password hash to binary file
    bool append_to_bin(std::ofstream& of_stream) const;
    //! Return whether password matches user's
    bool is_correct_password(const char* password) const;
    //! Add trip
    void add_trip(const Trip trip);
    //! Add friend
    void add_friend(String new_friend_username);
    //! Save information of user to file w/ same name
    bool save() const;
    //! Save only trips to file
    bool save_trips(std::ofstream& of_stream) const;
    //! Save friends to file
    bool save_friends(std::ofstream& of_stream) const;
    //! Save current user as friend in file
    bool save_as_friend(std::ofstream& of_stream) const;
    //! Load trips and friends from user file
    bool load();
    //! Load only trips from file
    bool load_trips(std::ifstream& if_stream);
    //! Load only friends from file
    bool load_friends(std::ifstream& if_stream);
};

#endif // USER_HPP
