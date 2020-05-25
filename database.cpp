#include <fstream>
#include <cstring>
#include "database.hpp"
#include "constants.hpp"


void Database::copy_from(const Database& other)
{
    this->destinations = other.destinations;
    this->curr_user = new User(*other.curr_user);
}

void Database::free_memory()
{
    delete this->curr_user;
}

Database::Database()
{
    this->curr_user = nullptr;
}

Database::Database(const Database& other)
{
    this->copy_from(other);
}

Database& Database::operator=(const Database& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->free_memory();
    this->copy_from(other);

    return *this;
}

Database::~Database()
{
    this->free_memory();
}

User* Database::get_user_by_username(const char* username) const
{
    String filename(DB_SUBDIR);
    filename += DB_FILENAME_USERS;

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
    filename += DB_FILENAME_USERS;

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
    users_db_filename += DB_FILENAME_USERS;

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

User* Database::get_curr_user() const
{
    return this->curr_user;
}

bool Database::log_in(const char* username, const char* password)
{
    if (this->curr_user)
    {
        return false;
    }

    User* found_user = this->get_user_by_username(username);
    if (!found_user)
    {
        return false;
    }

    if (!found_user->is_correct_password(password))
    {
        return false;
    }

    this->curr_user = found_user;
    return true;
}

bool Database::save_destinations()
{
    String dest_db_filename(DB_SUBDIR);
    dest_db_filename += DB_FILENAME_DESTINATIONS;

    std::ofstream of_stream(dest_db_filename.to_c_string(), std::ios::binary | std::ios::trunc);

    if (!of_stream)
    {
        return false;
    }

    const int destinations_count = this->destinations.get_len();
    for (size_t i = 0; i < destinations_count; ++i)
    {
        if (!this->destinations[i].write_to_bin(of_stream))
        {
            return false;
        }
    }

    return true;
}

bool Database::load_destinations()
{
    String dest_db_filename(DB_SUBDIR);
    dest_db_filename += DB_FILENAME_DESTINATIONS;

    std::ifstream if_stream(dest_db_filename.to_c_string(), std::ios::binary);

    if (!if_stream)
    {
        return false;
    }

    while (!if_stream.eof())
    {
        Destination dest;

        if (!dest.read_from_bin(if_stream))
        {
            break;
            return false;
        }

        this->destinations.push(dest);
    }

    return true;
}