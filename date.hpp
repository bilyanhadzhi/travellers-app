#ifndef DATE_HPP
#define DATE_HPP

class Date
{
private:
    int day;
    int month;
    int year;
    bool is_valid_date_string(const char* date_string);
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
};

#endif // DATE_HPP
