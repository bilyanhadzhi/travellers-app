#ifndef TRIP_HPP
#define TRIP_HPP

#include <iostream>
#include <fstream>
#include "destination.hpp"
#include "date.hpp"
#include "lib/vector.hpp"
#include "comment.hpp"

class Trip
{
private:
    Comment comment;
    Vector<String> photo_names;
    Date start_date;
    Date end_date;
    String destination_name;
    int rating;

public:
    Trip(String dest_name, Date start_date, Date end_date, int rating, Comment comment, Vector<String> photos);
    Trip(std::ifstream& if_stream);
    bool write_to_bin(std::ofstream& if_stream);
    bool read_from_bin(std::ifstream& of_stream);
    Comment get_comment() const;
    Vector<String> get_photo_names() const;
    Date get_start_date() const;
    Date get_end_date() const;
    String get_destination_name() const;
    int get_rating() const;
};

std::ostream& operator<<(std::ostream& o_stream, const Trip& trip);

#endif // TRIP_HPP
