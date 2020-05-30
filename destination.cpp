#include <fstream>
#include <iomanip>
#include <cassert>
#include "destination.hpp"
#include "constants.hpp"

Destination::Destination(String name)
{
    this->name = name;
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

bool Destination::write_to_bin(std::ofstream& of_stream) const
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

bool Destination::set_acc_rating(double acc_rating)
{
    assert(this->num_visits >= 0);

    if (this->num_visits == 0)
    {
        this->acc_rating = 0;
        return true;
    }

    if (acc_rating / num_visits < DEST_MIN_RATING || acc_rating / num_visits > DEST_MAX_RATING)
    {
        return false;
    }

    this->acc_rating = acc_rating;
}

bool Destination::set_num_visits(int num_visits)
{
    assert(num_visits >= 0);

    this->num_visits = num_visits;
}

String Destination::get_name() const
{
    return this->name;
}

int Destination::get_num_visits() const
{
    return this->num_visits;
}

double Destination::get_avg_rating() const
{
    if (this->num_visits < 1)
    {
        return 0.0;
    }

    return this->acc_rating / this->num_visits;
}

bool Destination::add_visit(double rating)
{
    if (rating < DEST_MIN_RATING || rating > DEST_MAX_RATING)
    {
        return false;
    }

    this->acc_rating += rating;
    this->num_visits++;
}

std::ostream& operator<<(std::ostream& o_stream, const Destination& destination)
{
    o_stream << std::setw(25) << std::left << destination.get_name() << " | ";
    o_stream << std::setw(4) << std::right << destination.get_num_visits() << " | ";
    o_stream << std::setw(6) << std::setprecision(3) << std::right << destination.get_avg_rating() << " |";
}
