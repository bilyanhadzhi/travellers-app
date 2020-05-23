#include <cstring>
#include <cctype>
#include "date.hpp"

Date::Date()
{
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

Date::Date(const char* date_string)
{
    this->set_date(date_string);
}

bool Date::is_valid_date_string(const char* date_string)
{
    bool is_valid = true;
    const int iso_date_len = 10;

    // check len == 10
    is_valid = strlen(date_string) == iso_date_len;

    for (int i = 0; i < iso_date_len; ++i)
    {
        if (!isdigit(date_string[i]) && i != 4 && i != 7)
        {
            is_valid = false;
        }
    }

    return is_valid;
}

bool Date::set_date(const char* date_string)
{
    if (!is_valid_date_string(date_string))
    {
        return false;
    }
}

int Date::get_day() const
{
    return this->day;
}

int Date::get_month() const
{
    return this->month;
}

int Date::get_year() const
{
    return this->year;
}
