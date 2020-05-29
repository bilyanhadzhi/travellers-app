#include <iostream>
#include <fstream>
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
    // test_date();
    test_app();

    return 0;
}

void test_app()
{
    TravellersApp app;
    app.run();
}

void test_date()
{
    Date new_date("1995-01-01");

    return;
}

void test_trip()
{
    // std::cout << sizeof(Trip) << "\n";
}

void test_destination()
{
    Destination dest("Paris", 4.78, 64000);

    String test_ofstream_file(DB_SUBDIR);
    test_ofstream_file += DB_FILENAME_DESTINATIONS;
    std::ofstream test_ofstream(test_ofstream_file.to_c_string(), std::ios::binary | std::ios::trunc);

    dest.write_to_bin(test_ofstream);
}

void test_user()
{
    User user;

    user.set_password("MyPassword5500");
    std::cout << user.is_correct_password("MyPassword5500") << "\n";
}

void test_string()
{
    String my_string;

    my_string.input(std::cin, false, '\"');

    std::cout << my_string << "\n";
}
