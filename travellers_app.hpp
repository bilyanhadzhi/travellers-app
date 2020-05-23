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
    void handle_command_register();
    void handle_command_log_in();

public:
    //! Run app's main loop
    void run();

};

#endif // TRAVELLERS_APP_HPP
