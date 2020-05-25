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
        else if (command == COMMAND_ADD_DESTINATION)
        {
            this->handle_command_add_destination();
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
            this->database.save_destinations();
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

bool TravellersApp::is_logged_in()
{
    return this->database.get_curr_user() != nullptr;
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

    if (this->is_logged_in())
    {
        this->io_handler.print_error("User currently logged in");
        return;
    }

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

    if (this->is_logged_in())
    {
        this->io_handler.print_error("User currently logged in");
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

        if (!this->is_logged_in())
        {
            this->io_handler.print_not_logged_in();
        }
        else
        {
            this->io_handler.print_usage(COMMAND_DESTINATIONS);
        }

        std::cin.ignore();
        return;
    }

    if (!this->is_logged_in())
    {
        this->io_handler.print_not_logged_in();
        return;
    }

    const Vector<Destination> all_destinations = this->database.get_destinations();
    const int destination_count = all_destinations.get_len();

    for (int i = 0; i < destination_count; ++i)
    {
        std::cout << all_destinations[i].get_name() << "\n";
    }
}

void TravellersApp::handle_command_add_destination()
{
    if (std::cin.peek() == '\n')
    {
        if (!this->is_logged_in())
        {
            this->io_handler.print_not_logged_in();
        }
        else
        {
            this->io_handler.print_usage(COMMAND_ADD_DESTINATION, USAGE_ADD_DESTINATION);
        }

        std::cin.ignore();
        return;
    }

    bool is_logged_in = this->is_logged_in();

    String dest_name;

    if (std::cin.peek() == '"')
    {
        std::cin.get();
        dest_name.input(std::cin, false, '\"');

        if (!is_logged_in)
        {
            this->io_handler.print_not_logged_in();
            return;
        }
    }
    else
    {
        this->io_handler.input_args(std::cin);

        if (!is_logged_in)
        {
            this->io_handler.print_not_logged_in();
            return;
        }

        if (!this->io_handler.check_number_of_arguments(1))
        {
            this->io_handler.print_usage(COMMAND_ADD_DESTINATION, USAGE_ADD_DESTINATION);
            return;
        }

        Vector<String> arguments = this->io_handler.get_args();

        dest_name = arguments[0];
    }

    Destination* existing_destination = this->database.get_destination_by_name(dest_name.to_c_string());
    if (existing_destination)
    {
        this->io_handler.print_error("Destination already exists");
        return;
    }

    Destination new_dest(dest_name);
    this->database.add_destination(new_dest);
}

void TravellersApp::handle_command_my_trips()
{
    if (std::cin.peek() != '\n')
    {
        this->io_handler.input_args(std::cin);

        if (!this->is_logged_in())
        {
            this->io_handler.print_not_logged_in();
        }
        else
        {
            this->io_handler.print_usage(COMMAND_MY_TRIPS);
        }

        std::cin.ignore();
        return;
    }

    if (!this->is_logged_in())
    {
        this->io_handler.print_not_logged_in();
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
