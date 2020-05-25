#include <fstream>
#include "destination.hpp"

Destination::Destination()
{
    this->name = "";
    this->acc_rating = 0.0;
    this->num_visits = 0;
}

Destination::Destination(String name, double acc_rating, int num_visits)
{
    this->name = name;
    this->acc_rating = acc_rating;
    this->num_visits = num_visits;
}

bool Destination::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    String dest_name;
    dest_name.read_from_bin(if_stream);

    double acc_rating;
    if_stream.read((char*)&acc_rating, sizeof(double));

    int num_visits;
    if_stream.read((char*)&num_visits, sizeof(int));

    if (!if_stream)
    {
        return false;
    }

    this->name = dest_name;
    this->acc_rating = acc_rating;
    this->num_visits = num_visits;
    return true;
}

bool Destination::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    this->name.write_to_bin(of_stream);
    of_stream.write((char*)&this->acc_rating, sizeof(double));
    of_stream.write((char*)&this->num_visits, sizeof(int));

    if (!of_stream)
    {
        return false;
    }

    return true;
}
