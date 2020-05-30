#include <fstream>
#include <cctype>
#include "user.hpp"
#include "bcrypt/BCrypt.hpp"

User::User()
{
    this->username = "";
    this->email = "";
    this->password_hash = "";
}

User::User(String username, String email, String password_hash)
{
    this->set_username(username);
    this->set_email(email);
    this->set_password_hash(password_hash);

    this->load();
}

bool User::is_valid_username(String username) const
{
    bool is_valid = true;
    const int len = username.get_len();
    bool contains_alpha = false;

    if (len > MAX_USERNAME_LEN)
    {
        is_valid = false;
    }

    for (int i = 0; i < len && is_valid; ++i)
    {
        if (!isalnum(username[i]) && username[i] != '_' && username[i] != '.')
        {
            is_valid = false;
        }
        contains_alpha = contains_alpha || isalpha(username[i]);
    }

    is_valid = is_valid && contains_alpha;

    return is_valid;
}

bool User::is_valid_password(String password) const
{
    const int len = password.get_len();

    bool contains_upper = false;
    bool contains_lower = false;
    bool contains_digit = false;
    bool contains_non_ascii = false;
    bool is_valid = false;

    for (int i = 0; i < len; ++i)
    {
        contains_lower = contains_lower || islower(password[i]);
        contains_upper = contains_upper || isupper(password[i]);
        contains_digit = contains_digit || isdigit(password[i]);
        contains_non_ascii = contains_non_ascii || !isascii(password[i]);
    }

    is_valid = len >= MIN_PASSWORD_LEN;
    is_valid = is_valid && contains_digit && contains_lower && contains_upper && !contains_non_ascii;
    return is_valid;
}

bool User::is_valid_email(String email) const
{
    const int len = email.get_len();
    bool is_valid = false;

    int at_sign_index = -1;
    int dot_index = -1;
    bool contains_non_ascii = false;

    for (int i = len - 1; i >= 0; --i)
    {
        contains_non_ascii = contains_non_ascii || !isascii(email[i]);

        if (email[i] == '.' && dot_index == -1)
        {
            dot_index = i;
        }

        if (email[i] == '@' && at_sign_index == -1)
        {
            at_sign_index = i;
        }
    }

    is_valid = (at_sign_index != -1 && dot_index != -1);
    is_valid = is_valid && (dot_index < len - 1);
    is_valid = is_valid && (dot_index - at_sign_index >= 1);

    return is_valid;
}

bool User::set_username(String username)
{
    if (!this->is_valid_username(username))
    {
        return false;
    }

    // TODO: check if username is free

    this->username = username;
    return true;
}

bool User::set_password(String password)
{
    if (!this->is_valid_password(password))
    {
        return false;
    }

    String hash = BCrypt::generateHash(password.to_c_string());

    this->password_hash = hash;
    return true;
}

void User::set_password_hash(String password_hash)
{
    this->password_hash = password_hash;
}

bool User::set_email(String email)
{
    if (!this->is_valid_email(email))
    {
        return false;
    }

    // TODO: check if email is free

    this->email = email;
    return true;
}

String User::get_username() const
{
    return this->username;
}

String User::get_email() const
{
    return this->email;
}

String User::get_password_hash() const
{
    return this->password_hash;
}

bool User::append_to_bin(std::ofstream& of_stream) const
{
    return this->username.write_to_bin(of_stream) && this->email.write_to_bin(of_stream)
            && this->password_hash.write_to_bin(of_stream);
}

bool User::is_correct_password(const char* password) const
{
    return BCrypt::validatePassword(password, this->password_hash.to_c_string());
}

void User::add_trip(const Trip trip)
{
    this->trips.push(trip);
}

void User::add_friend(String new_friend_username)
{
    this->friends_usernames.push(new_friend_username);
}

Vector<String> User::get_friends_usernames() const
{
    return this->friends_usernames;
}

Vector<Trip> User::get_trips() const
{
    return this->trips;
}

bool User::save() const
{
    String user_filename = DB_USERS_SUBDIR;
    user_filename += this->get_username();
    user_filename += DB_EXTENSION;

    std::ofstream of_stream(user_filename.to_c_string(), std::ios::binary | std::ios::trunc);

    if (this->trips.get_len() < 1)
    {
        std::cout << "peace\n";
        return true;
    }

    return this->save_trips(of_stream);
}

bool User::save_trips(std::ofstream& of_stream) const
{
    if (!of_stream)
    {
        return false;
    }

    const int number_of_trips = this->trips.get_len();

    of_stream.write((char*)&number_of_trips, sizeof(int));
    for (int i = 0; i < number_of_trips; ++i)
    {
        this->trips[i].write_to_bin(of_stream);
    }

    return of_stream ? true : false;
}

bool User::save_friends(std::ofstream& of_stream) const
{
    const int friends_usernames_count = this->friends_usernames.get_len();

    for (int i = 0; i < friends_usernames_count; ++i)
    {
        this->friends_usernames[i].write_to_bin(of_stream);
    }

    return of_stream ? true : false;
}

bool User::load()
{
    String user_filename = DB_USERS_SUBDIR;
    user_filename += this->get_username();
    user_filename += DB_EXTENSION;

    std::ifstream if_stream(user_filename.to_c_string(), std::ios::binary);

    return this->load_trips(if_stream) && this->load_friends(if_stream);
}

bool User::load_trips(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    if_stream.seekg(std::ios::beg);
    if (if_stream.peek() == EOF)
    {
        return false;
    }

    Vector<Destination> destinations;

    int number_of_trips = 0;
    if_stream.read((char*)&number_of_trips, sizeof(int));

    for (int i = 0; i < number_of_trips; ++i)
    {
        Trip to_add(if_stream);
        this->trips.push(to_add);
    }

    return if_stream ? true : false;
}

bool User::load_friends(std::ifstream& if_stream)
{
    if (!if_stream || if_stream.peek() == EOF)
    {
        return false;
    }

    int friends_usernames_count;
    if_stream.read((char*)&friends_usernames_count, sizeof(int));

    for (int i = 0; i < friends_usernames_count; ++i)
    {
        String friend_username;
        friend_username.read_from_bin(if_stream);

        this->friends_usernames.push(friend_username);
    }

    return if_stream ? true : false;
}
