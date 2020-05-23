#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "trip.hpp"
#include "destination.hpp"
#include "user.hpp"

class Database
{
private:
    User curr_user;
    Vector<Destination> destinations;
    //! Dummy function
    void populate_data();
public:
    Database();
};

#endif // DATABASE_HPP
