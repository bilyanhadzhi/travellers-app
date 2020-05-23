#include "user.hpp"
#include <cctype>
#include "bcrypt/BCrypt.hpp"

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

    std::cout << hash << "\n";

    this->password_hash = hash;
    return true;
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

bool User::is_correct_password(const char* password) const
{
    return BCrypt::validatePassword(password, this->password_hash.to_c_string());
}
