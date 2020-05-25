#include <iostream>
#include "date.hpp"
#include "trip.hpp"
#include "destination.hpp"
#include "user.hpp"
#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "travellers_app.hpp"

void test_date();
void test_destination();
void test_trip();
void test_user();
void test_app();
void test_string();

int main(void)
{
    // test_trip();
    // test_destination();
    // test_user();
    // test_string();
    test_app();

    return 0;
}

void test_app()
{
    TravellersApp app;
    app.run();
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
    User user;

    user.set_password("MyPassword5500");
    std::cout << user.is_correct_password("MyPassword5500") << "\n";
}

void test_string()
{
    String my_string("hello");

    my_string += " world";

    std::cout << my_string << "\n";
}
