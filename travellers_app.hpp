#ifndef TRAVELLERS_APP_HPP
#define TRAVELLERS_APP_HPP

#include "io_handler.hpp"
#include "user.hpp"
#include "database.hpp"

class TravellersApp
{
private:
    Database database;
    IOHandler io_handler;
    bool is_logged_in();
    void handle_command_register();
    void handle_command_log_in();
    void handle_command_destinations();
    void handle_command_add_destination();
    void handle_command_my_trips();
    void handle_command_add_trip();
    void handle_command_help();
public:
    //! Run app's main loop
    void run();

};

#endif // TRAVELLERS_APP_HPP
