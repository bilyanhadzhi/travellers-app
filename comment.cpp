#include "comment.hpp"

Comment::Comment(String value, String from)
{
    this->value = value;
    this->from = from;
}

bool Comment::write_to_bin(std::ofstream& of_stream)
{
    return this->value.write_to_bin(of_stream) && this->from.write_to_bin(of_stream);
}

bool Comment::read_from_bin(std::ifstream& if_stream)
{
    return this->value.read_from_bin(if_stream) && this->from.read_from_bin(if_stream);
}

String Comment::get_value() const
{
    return this->value;
}

String Comment::get_from() const
{
    return this->from;
}
