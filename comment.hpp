#include <fstream>
#include "lib/string.hpp"

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
};
