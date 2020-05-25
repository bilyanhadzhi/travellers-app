#ifndef DESTINATION_HPP
#define DESTINATION_HPP

#include "lib/string.hpp"

class Destination
{
private:
    String name;
    double acc_rating;
    int num_visits;
    bool set_acc_rating(double acc_rating);
    bool set_num_visits(int num_visits);

public:
    Destination(String name = "");
    Destination(String name, double acc_rating, int num_visits);
    //! Load destination from binary file
    bool read_from_bin(std::ifstream& if_stream);
    //! Write destination to binary file
    bool write_to_bin(std::ofstream& of_stream);
    //! Get destination name
    String get_name() const;
    //! Get number of visits of destination
    int get_num_visits() const;
    //! Get average rating of trips to destination
    double get_avg_rating() const;
    //! Add a visit entry with a rating
    bool add_visit(double rating);
};

#endif // DESTINATION_HPP
