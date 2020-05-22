#include <iostream>
#include "date.hpp"
#include "trip.hpp"
#include "destination.hpp"
#include "user.hpp"
#include "lib/string.hpp"
#include "lib/vector.hpp"

void test_date();
void test_destination();
void test_trip();
void test_user();
void test_app();

int main(void)
{
    // test_trip();
    // test_destination();
    // test_user();

    return 0;
}

void test_trip()
{
    Trip trip1;
    std::cout << sizeof(Trip) << "\n";
}

void test_destination()
{
    std::cout << sizeof(Destination) << "\n";
}

void test_user()
{
    std::cout << sizeof(User) << "\n";
}
