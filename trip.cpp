#include "trip.hpp"

Trip::Trip(Destination* destination, Date start_date, Date end_date, int rating, String comment, Vector<String> photos)
{
    this->destination = destination;
    this->start_date = start_date;
    this->end_date = end_date;
    this->rating = rating;
    this->comment = comment;
    this->photo_names = photos;
}
