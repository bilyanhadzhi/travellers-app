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
}
