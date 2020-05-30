#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <fstream>

//! A date, represented as day, month and year

class Date
{
private:
    int day;
    int month;
    int year;
public:
    //! Date defaults to 01-01-2000
    Date();
    //! Fill out date from ISO 8601 string (only set if valid, else default to 01-01-2000)
    Date(const char* date_string);
    //! Get date's day
    int get_day() const;
    //! Get date's month
    int get_month() const;
    //! Get date's year
    int get_year() const;
    //! Set date via string (only if valid)
    bool set_date(const char* date_string);
    //! Set date via numbers
    bool set_date(int day, int month, int year);
    //! Check if date string is valid
    bool is_valid_date_string(const char* date_string) const;
    //! Check if is a valid date
    bool is_valid_date(int day, int month, int year) const;
    //! Check if year is a leap year
    bool is_leap_year(int year) const;
    //! Write date as day->month->year in binary file
    bool write_to_bin(std::ofstream& of_stream);
    //! Read from binary file as day->month->year
    bool read_from_bin(std::ifstream& if_stream);
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& o_stream, const Date& date);

#endif // DATE_HPP
