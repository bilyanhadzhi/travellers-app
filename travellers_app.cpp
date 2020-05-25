#include "travellers_app.hpp"

void TravellersApp::run()
{
    do
    {
        this->io_handler.print_prompt();
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }

        this->io_handler.input_command();
        String command = this->io_handler.get_command();

        if (command == COMMAND_REGISTER)
        {
            this->handle_command_register();
        }
        else if (command == COMMAND_LOG_IN)
        {
            this->handle_command_log_in();
        }
        else if (command == COMMAND_DESTINATIONS)
        {
            this->handle_command_destinations();
        }
        else if (command == COMMAND_MY_TRIPS)
        {
            this->handle_command_my_trips();
        }
        else if (command == COMMAND_ADD_TRIP)
        {
            this->handle_command_add_trip();
        }
        else if (command == COMMAND_HELP)
        {
            this->handle_command_help();
        }
        else if (command == COMMAND_EXIT)
        {
            this->io_handler.print_message("Bye! :)");
        }
        else
        {
            if (std::cin.peek() == '\n')
            {
                std::cin.ignore();
                this->io_handler.print_unknown_command();
            }
            else
            {
                this->io_handler.input_args(std::cin);
                this->io_handler.print_unknown_command();
            }
        }
    }
    while (this->io_handler.get_command() != COMMAND_EXIT);
}

void TravellersApp::handle_command_register()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_REGISTER, USAGE_REGISTER);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(3))
    {
        this->io_handler.print_usage(COMMAND_REGISTER, USAGE_REGISTER);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();

    User to_be_registered;

    if (!to_be_registered.set_username(arguments[0]))
    {
        this->io_handler.print_error("Username not valid");
        return;
    }

    if (!to_be_registered.set_email(arguments[1]))
    {
        this->io_handler.print_error("Email not valid");
        return;
    }

    if (!to_be_registered.set_password(arguments[2]))
    {
        this->io_handler.print_error("Password not valid");
        this->io_handler.print_error_explain("The password must:");
        this->io_handler.print_error_explain("  – be at least 10 characters long");
        this->io_handler.print_error_explain("  – contain an uppercase character");
        this->io_handler.print_error_explain("  – contain a lowercase character");
        this->io_handler.print_error_explain("  – contain a numeric character");
        return;
    }

    // check for user with same username
    User* existing_user = this->database.get_user_by_username(arguments[0].to_c_string());
    if (existing_user)
    {
        this->io_handler.print_error("Username already taken");
        delete existing_user;
        return;
    }

    // check for user with same email
    existing_user = this->database.get_user_by_email(arguments[1].to_c_string());
    if (existing_user)
    {
        this->io_handler.print_error("Email already taken");
        delete existing_user;
        return;
    }

    if (!this->database.add_user(to_be_registered))
    {
        this->io_handler.print_error("User could not be registered");
        return;
    }
}

void TravellersApp::handle_command_log_in()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_LOG_IN, USAGE_LOG_IN);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);
    if (!this->io_handler.check_number_of_arguments(2))
    {
        this->io_handler.print_usage(COMMAND_LOG_IN, USAGE_LOG_IN);
        return;
    }

    if (this->database.get_curr_user())
    {
        this->io_handler.print_error("Another user is already logged in.");
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!this->database.log_in(arguments[0].to_c_string(), arguments[1].to_c_string()))
    {
        this->io_handler.print_error("No matching username/password for any user");
        return;
    }
    else
    {
        this->io_handler.print_success("Logged in");
        return;
    }
}

void TravellersApp::handle_command_destinations()
{
    if (std::cin.peek() != '\n')
    {
        this->io_handler.input_args(std::cin);
        this->io_handler.print_usage(COMMAND_DESTINATIONS);
        std::cin.ignore();
        return;
    }


}

void TravellersApp::handle_command_my_trips()
{
    if (std::cin.peek() != '\n')
    {
        this->io_handler.input_args(std::cin);
        this->io_handler.print_usage(COMMAND_MY_TRIPS);
        std::cin.ignore();
        return;
    }
}

void TravellersApp::handle_command_add_trip()
{

}

void TravellersApp::handle_command_help()
{
    if (std::cin.peek() != '\n')
    {
        this->io_handler.input_args(std::cin);
        this->io_handler.print_usage(COMMAND_HELP);
        std::cin.ignore();
        return;
    }
}
