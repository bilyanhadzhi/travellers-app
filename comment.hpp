#include <fstream>
#include "lib/string.hpp"

//! A comment to a Trip has the value of the comment itself, and the username of the commenter (i.e. the visitor)

class Comment
{
private:
    String value;
    String from;
public:
    Comment(String value, String from);
    //! Write comment string and username of user which posted it
    bool write_to_bin(std::ofstream& of_stream);
    //! Read comment string and username of poster
    bool read_from_bin(std::ifstream& if_stream);
    //! Get comment string
    String get_value() const;
    //! Get username string
    String get_from() const;
};
