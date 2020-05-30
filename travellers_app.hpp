#ifndef TRAVELLERS_APP_HPP
#define TRAVELLERS_APP_HPP

//! The outermost class of the application

#include "io_handler.hpp"
#include "user.hpp"
#include "database.hpp"

class TravellersApp
{
private:
    //! Database class, responsible for storing currently logged in user and all destinations.
    /*! The rest of the necessary information is gathered from the user file. */
    Database database;
    //! Input/output handler class, responsible for parsing command-line input and standardizing output.
    IOHandler io_handler;
    //! Return whether a user is currently logged in
    bool is_logged_in();
    void handle_command_register();
    void handle_command_log_in();
    void handle_command_destinations();
    void handle_command_add_destination();
    void handle_command_destination_info();
    void handle_command_my_friends();
    void handle_command_add_friend();
    void handle_command_my_trips();
    void handle_command_add_trip();
    void handle_command_log_out();
    void handle_command_help();
public:
    //! Run app's main loop
    void run();

};

#endif // TRAVELLERS_APP_HPP
