#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
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

Comment Trip::get_comment() const
{
    return this->comment;
}

Vector<String> Trip::get_photo_names() const
{
    return this->photo_names;
}

Date Trip::get_start_date() const
{
    return this->start_date;
}

Date Trip::get_end_date() const
{
    return this->end_date;
}

String Trip::get_destination_name() const
{
    return this->destination_name;
}

int Trip::get_rating() const
{
    return this->rating;
}

std::ostream& operator<<(std::ostream& o_stream, const Trip& trip)
{
    o_stream << std::left << std::setw(25) << trip.get_destination_name() << " | ";
    o_stream << std::right << std::setw(5) << trip.get_start_date() << " – " << trip.get_end_date() << " | ";
    o_stream << std::setw(3) << trip.get_rating() << "/" << DEST_MAX_RATING << " | ";

    String comment = trip.get_comment().get_value();
    const int comment_len = comment.get_len();
    if (comment_len > PRINT_MAX_DESC_LEN)
    {
        o_stream.write(trip.get_comment().get_value().to_c_string(), PRINT_MAX_DESC_LEN - 4);
        o_stream << " ... | ";
    }
    else
    {
        o_stream << std::left << std::setw(PRINT_MAX_DESC_LEN) << trip.get_comment().get_value() << " | ";
    }

    Vector<String> photo_names = trip.get_photo_names();
    const int photo_names_count = photo_names.get_len();

    String photo_names_output;

    for (int i = 0; i < photo_names_count; ++i)
    {
        photo_names_output += photo_names[i];
        photo_names_output += " ";
    }

if (photo_names_output.get_len() > PRINT_MAX_PHOTO_NAMES_LEN)
    {
        o_stream.write(photo_names_output.to_c_string(), PRINT_MAX_PHOTO_NAMES_LEN - 4);
        o_stream << " ... | ";
    }
    else
    {
        o_stream << std::left << std::setw(PRINT_MAX_PHOTO_NAMES_LEN) << photo_names_output << " |";
    }

    return o_stream;
}
