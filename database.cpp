#include <fstream>
#include <cstring>
#include "database.hpp"
#include "constants.hpp"

Database::Database()
{

}

User* Database::get_user_by_username(const char* username) const
{
    String filename(DB_SUBDIR);
    filename += FILENAME_USERS_DB;

    std::ifstream if_stream(filename.to_c_string(), std::ios::binary);

    if (!if_stream)
    {
        return nullptr;
    }

    User* found_user = nullptr;
    String found_username;
    String found_email;
    String found_password_hash;

    bool found = false;
    while (!found && !if_stream.eof())
    {
        found_username.read_from_bin(if_stream);
        found_email.read_from_bin(if_stream);
        found_password_hash.read_from_bin(if_stream);

        if (found_username == username)
        {
            found = true;
        }
    }

    if (found)
    {
        found_user = new User(found_username, found_email, found_password_hash);
    }

    return found_user;
}

User* Database::get_user_by_email(const char* email) const
{
    String filename(DB_SUBDIR);
    filename += FILENAME_USERS_DB;

    std::ifstream if_stream(filename.to_c_string(), std::ios::binary);

    if (!if_stream)
    {
        return nullptr;
    }

    User* found_user = nullptr;
    String found_username;
    String found_email;
    String found_password_hash;

    bool found = false;
    while (!found && !if_stream.eof())
    {
        found_username.read_from_bin(if_stream);
        found_email.read_from_bin(if_stream);
        found_password_hash.read_from_bin(if_stream);

        if (found_email == email)
        {
            found = true;
        }
    }

    if (found)
    {
        found_user = new User(found_username, found_email, found_password_hash);
    }

    return found_user;
}

bool Database::add_user(User user) const
{
    String users_db_filename(DB_SUBDIR);
    users_db_filename += FILENAME_USERS_DB;

    std::ofstream users_file(users_db_filename.to_c_string(), std::ios::binary | std::ios::app);

    if (!users_file)
    {
        return false;
    }

    bool result = user.append_to_bin(users_file);

    String curr_user_db_filename(DB_USERS_SUBDIR);
    curr_user_db_filename += user.get_username();
    curr_user_db_filename += DB_EXTENSION;

    std::ofstream new_user_db(curr_user_db_filename.to_c_string(), std::ios::binary);

    return result;
}

bool Database::register_user(User user) const
{
    // add user to users.db


    // make personal db file
}
