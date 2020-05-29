#ifndef TRIP_HPP
#define TRIP_HPP

#include "destination.hpp"
#include "date.hpp"
#include "lib/vector.hpp"

class Trip
{
private:
    String comment;
    Vector<String> photo_names;
    Date start_date;
    Date end_date;
    Destination* destination;
    int rating;

public:
    Trip(Destination* destination, Date start_date, Date end_date, int rating, String comment, Vector<String> photos);
};

#endif // TRIP_HPP
