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
    Date();
    Date(const char* date_string);
    int get_day() const;
    int get_month() const;
    int get_year() const;
    bool set_date(const char* date_string);
};

#endif // DATE_HPP
