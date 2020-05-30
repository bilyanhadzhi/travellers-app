#ifndef TRIP_HPP
#define TRIP_HPP

#include <iostream>
#include <fstream>
#include "destination.hpp"
#include "date.hpp"
#include "lib/vector.hpp"
#include "comment.hpp"

//! Contains information about a Trip from a User

/*!
    Each trip has a destination name, a time period (two Date objects), rating (1-5),
    a Comment object and a list of photo filenames. The comment has the username of
    the User who made the visit, allowing identification later on.

    The comment can be empty, as well as the photo filenames list. The beginning date
    can match the ending date for a trip period of a single day.
*/

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
    //! Constructor for creating a new Trip
    Trip(String dest_name, Date start_date, Date end_date, int rating, Comment comment, Vector<String> photos);
    //! Constructor for creating a Trip instance out of a file
    Trip(std::ifstream& if_stream);
    //! Write the trip's information to a binary file
    bool write_to_bin(std::ofstream& if_stream);
    //! Load the trip's information from a binary file
    bool read_from_bin(std::ifstream& of_stream);
    //! Get copy of the trip's comment
    Comment get_comment() const;
    //! Get copy of photo filenames list
    Vector<String> get_photo_names() const;
    //! Get beginning date of trip
    Date get_start_date() const;
    //! Get end date of trip (can only be >= beginning)
    Date get_end_date() const;
    //! Get copy of the destination's name
    String get_destination_name() const;
    //! Get copy of the rating of this Trip
    int get_rating() const;
};

std::ostream& operator<<(std::ostream& o_stream, const Trip& trip);

#endif // TRIP_HPP
