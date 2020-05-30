#ifndef DESTINATION_HPP
#define DESTINATION_HPP

#include <iostream>
#include <fstream>
#include "lib/string.hpp"

//! Simple destination class, containing its name, number of visits, and rating.
/*!
    Due to the nature of the file structure, trips are not stored as part of this
    class. Trips are stored for each user, instead of for each destination.
*/

class Destination
{
private:
    String name;
    double acc_rating;
    int num_visits;
    bool set_acc_rating(double acc_rating);
    bool set_num_visits(int num_visits);

public:
    //! The most-used constructor, for when creating a new destination. (can be default for array purposes)
    Destination(String name = "");
    //! Full constructor
    Destination(String name, double acc_rating, int num_visits);
    //! Load destination from binary file
    bool read_from_bin(std::ifstream& if_stream);
    //! Write destination to binary file
    bool write_to_bin(std::ofstream& of_stream) const;
    //! Get destination name
    String get_name() const;
    //! Get number of visits of destination
    int get_num_visits() const;
    //! Get average rating of trips to destination
    double get_avg_rating() const;
    //! Add a visit entry with a rating
    bool add_visit(double rating);
};

//! Pretty-print the destination's name, number of visits and average rating
std::ostream& operator<<(std::ostream& o_stream, const Destination& destination);

#endif // DESTINATION_HPP
