#ifndef TRIP_HPP
#define TRIP_HPP

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
};

#endif // TRIP_HPP
