#include <iostream>
#include <cstring>

#include "io_handler.hpp"

#include "lib/string.hpp"
#include "constants.hpp"

void IOHandler::set_command(String command)
{
    this->command = command;
}

void IOHandler::input_command()
{
    std::cin >> this->command;
}

void IOHandler::input_args(std::istream& i_stream)
{
    this->clean_args();

    String args_string = "";
    args_string.input(i_stream, true);

    if (args_string == "")
    {
        return;
    }

    String curr_arg;
    int args_str_len = args_string.get_len();
    int i = 0;
    while (args_string[i] == ' ')
    {
        ++i;
    }

    while (i < args_str_len)
    {
        if (args_string[i] != ' ')
        {
            curr_arg += args_string[i];
            ++i;
        }
        else
        {
            while (args_string[i] == ' ')
            {
                ++i;
            }
            curr_arg += '\0';
            this->args.push(curr_arg);
            curr_arg = "";
        }
    }

    if (curr_arg != "")
    {
        this->args.push(curr_arg);
    }

    return;
}

String IOHandler::get_command() const
{
    return this->command;
}

Vector<String> IOHandler::get_args() const
{
    return this->args;
}

void IOHandler::clean_args()
{
    this->args.empty_vector();
}

bool IOHandler::check_number_of_arguments(int num_of_args) const
{
    return this->args.get_len() == num_of_args;
}

void IOHandler::print_prompt() const
{
    std::cout << SHELL_PROMPT;
}

void IOHandler::print_message(String message, String prefix) const
{
    if (prefix.get_len() > 0)
    {
        std::cout << prefix << ": ";
    }

    if (message.get_len() > 0)
    {
        std::cout << message << std::endl;
    }
}

void IOHandler::print_usage(String command, String usage, bool with_prefix) const
{
    if (with_prefix)
    {
        std::cout << "Usage: ";
    }

    std::cout << command;

    if (usage.get_len() > 0)
    {
        std::cout << " " << usage << std::endl;
    }
    else
    {
        std::cout << " (no args)" << std::endl;
    }
}

void IOHandler::print_error(String desc) const
{
    this->print_message(desc, "Error");
}

void IOHandler::print_not_logged_in() const
{
    this->print_error("No user is currently logged in");
}

void IOHandler::print_error_explain(String desc) const
{
    std::cout << "       ";
    std::cout << desc << std::endl;
}

void IOHandler::print_unknown_command() const
{
    this->print_message("Unknown command. Type 'help' for a list of commands.");
}

void IOHandler::print_success(String message) const
{
    this->print_message(message, "Success");
}

void IOHandler::print_help() const
{
    this->print_message("\nTraveller's App commands:\n");

    this->print_usage(COMMAND_REGISTER, USAGE_REGISTER, false);
    this->print_message("  – adds a new user.\n");

    this->print_usage(COMMAND_LOG_IN, USAGE_LOG_IN, false);
    this->print_message("  – logs user in via username.\n");

    this->print_usage(COMMAND_DESTINATIONS, "", false);
    this->print_message("  – displays all destinations with their name, number of visits and average rating.\n");

    this->print_usage(COMMAND_ADD_DESTINATION, USAGE_ADD_DESTINATION, false);
    this->print_message("  – adds a new destination to the database.\n");

    this->print_usage(COMMAND_DESTINATION_INFO, USAGE_DESTINATION_INFO, false);
    this->print_message("  – displays additional information about a destination, including visits by friends.\n");

    this->print_usage(COMMAND_MY_TRIPS, "", false);
    this->print_message("  – displays all trips of current user.\n");

    this->print_usage(COMMAND_ADD_TRIP, "", false);
    this->print_message("  – interactive command to add a new trip.\n");

    this->print_usage(COMMAND_MY_FRIENDS, "", false);
    this->print_message("  – displays friends of current user.\n");

    this->print_usage(COMMAND_ADD_FRIEND, USAGE_ADD_FRIEND, false);
    this->print_message("  – adds new friend for user.\n");

    this->print_usage(COMMAND_LOG_OUT, "", false);
    this->print_message("  – logs current user out.\n");

    this->print_usage(COMMAND_HELP, "", false);
    this->print_message("  – shows possible commands of application.\n");

    this->print_usage(COMMAND_EXIT, "", false);
    this->print_message("  – exits the application.\n");
}
