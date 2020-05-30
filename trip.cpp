#include <fstream>
#include <cassert>
#include "trip.hpp"

Trip::Trip(String dest_name, Date start_date, Date end_date, int rating, Comment comment, Vector<String> photos):
    comment(comment)
{
    this->destination_name = dest_name;
    this->start_date = start_date;
    this->end_date = end_date;
    this->rating = rating;
    this->photo_names = photos;
}

Trip::Trip(std::ifstream& if_stream): comment("", "")
{
    this->read_from_bin(if_stream);
}

bool Trip::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    this->destination_name.write_to_bin(of_stream);

    this->start_date.write_to_bin(of_stream);
    this->end_date.write_to_bin(of_stream);

    this->comment.write_to_bin(of_stream);

    of_stream.write((char*)&this->rating, sizeof(int));

    const int photos_count = this->photo_names.get_len();
    of_stream.write((char*)&photos_count, sizeof(int));

    for (int i = 0; i < photos_count; ++i)
    {
        this->photo_names[i].write_to_bin(of_stream);
    }

    return of_stream ? true : false;
}

bool Trip::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    this->destination_name.read_from_bin(if_stream);

    this->start_date.read_from_bin(if_stream);
    this->end_date.read_from_bin(if_stream);

    this->comment.read_from_bin(if_stream);

    if_stream.read((char*)&this->rating, sizeof(int));

    int photos_count = 0;
    if_stream.read((char*)&photos_count, sizeof(int));

    for (int i = 0; i < photos_count; ++i)
    {
        String photo_name_i;
        photo_name_i.read_from_bin(if_stream);

        this->photo_names.push(photo_name_i);
    }

    return if_stream ? true : false;
}
