#include <cstring>
#include <cctype>
#include "date.hpp"
#include "lib/string.hpp"

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

bool Date::is_valid_date_string(const char* date_string) const
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

bool Date::is_valid_date(int day, int month, int year) const
{
    bool is_valid = true;

    if (day < 1 || month < 1 || year < 1)
    {
        is_valid = false;
    }

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (day > 31)
        {
            is_valid = false;
        }
        break;
    case 2:
        if (day > 29)
        {
            is_valid = false;
        }
        else if (day == 29)
        {
            if (!this->is_leap_year(year))
            {
                is_valid = false;
            }
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30)
        {
            is_valid = false;
        }
        break;
    default:
        is_valid = false;
        break;
    }

    return is_valid;
}

bool Date::is_leap_year(int year) const
{
    if (year < 1)
    {
        return false;
    }

    if (year % 400 == 0)
    {
        return false;
    }

    if (year % 100 == 0)
    {
        return true;
    }

    if (year % 4 == 0)
    {
        return true;
    }

    return false;
}

bool Date::set_date(const char* date_string)
{
    if (!is_valid_date_string(date_string))
    {
        return false;
    }

    String day_string;
    day_string += date_string[8];
    day_string += date_string[9];

    String month_string;
    month_string += date_string[5];
    month_string += date_string[6];

    String year_string;
    year_string += date_string[0];
    year_string += date_string[1];
    year_string += date_string[2];
    year_string += date_string[3];

    int day = day_string.to_int();
    int month = month_string.to_int();
    int year = year_string.to_int();

    if (!this->is_valid_date(day, month, year))
    {
        return false;
    }

    this->set_date(day, month, year);
    return true;
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

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.get_day() == rhs.get_day() && lhs.get_month() == rhs.get_month() && lhs.get_year() == rhs.get_year();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs)
{
    if (lhs.get_year() > rhs.get_year())
    {
        return true;
    }
    else if (lhs.get_year() == rhs.get_year())
    {
        if (lhs.get_month() > rhs.get_month())
        {
            return true;
        }
        else if (lhs.get_month() == rhs.get_month())
        {
            if (lhs.get_day() > rhs.get_day())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return !(lhs == rhs) && !(lhs > rhs);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
    return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
    return !(lhs > rhs);
}


bool Date::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    of_stream.write((char*)&this->day, sizeof(int));
    of_stream.write((char*)&this->month, sizeof(int));
    of_stream.write((char*)&this->year, sizeof(int));

    return of_stream ? true : false;
}

bool Date::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    int day, month, year;
    if_stream.read((char*)&day, sizeof(int));
    if_stream.read((char*)&month, sizeof(int));
    if_stream.read((char*)&year, sizeof(int));

    return this->set_date(day, month, year);
}

bool Date::set_date(int day, int month, int year)
{
    if (!this->is_valid_date(day, month, year))
    {
        return false;
    }

    this->day = day;
    this->month = month;
    this->year = year;
    return true;
}
