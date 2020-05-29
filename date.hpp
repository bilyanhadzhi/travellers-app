#ifndef DATE_HPP
#define DATE_HPP

class Date
{
private:
    int day;
    int month;
    int year;
public:
    //! Date defaults to 01.01.1960
    Date();
    Date(const char* date_string);
    //! Get date's day
    int get_day() const;
    //! Get date's month
    int get_month() const;
    //! Get date's year
    int get_year() const;
    //! Set date via string (only if valid)
    bool set_date(const char* date_string);
    //! Check if date string is valid
    bool is_valid_date_string(const char* date_string) const;
    //! Check if is a valid date
    bool is_valid_date(int day, int month, int year) const;
    //! Check if year is a leap year
    bool is_leap_year(int year) const;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);

#endif // DATE_HPP
