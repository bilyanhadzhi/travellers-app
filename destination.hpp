#ifndef DESTINATION_HPP
#define DESTINATION_HPP

#include "lib/string.hpp"

class Destination
{
private:
    String name;
    double acc_rating;
    int num_visits;

public:
    Destination();
    Destination(String name, double acc_rating, int num_visits);
    //! Load destination from binary file
    bool read_from_bin(std::ifstream& if_stream);
    //! Write destination to binary file
    bool write_to_bin(std::ofstream& of_stream);
};

#endif // DESTINATION_HPP
