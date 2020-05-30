#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"

//! A helper class to handle parsing commands and arguments.

class IOHandler
{
private:
    String command;
    Vector<String> args;
    void set_command(String command);
    void clean_args();

public:
    //! Get first string from the console
    void input_command();
    //! Get arguments, separated by space
    void input_args(std::istream& i_stream);
    //! Get current command
    String get_command() const;
    //! Get current arguments in a list
    Vector<String> get_args() const;
    //! Returns whether the number of current arguments is 'num_of_args'
    bool check_number_of_arguments(int num_of_args) const;
    //! Print message
    void print_message(String message, String prefix = "") const;
    //! Print shell prompt
    void print_prompt() const;
    //! Print usage of command
    void print_usage(String command, String usage = "", bool with_prefix = true) const;
    //! Print error with description
    void print_error(String desc) const;
    //! Print that there is no logged in user
    void print_not_logged_in() const;
    //! Same as print error, but without the "Error: " prefix
    void print_error_explain(String desc) const;
    //! Print unknown command
    void print_unknown_command() const;
    //! Print success with message
    void print_success(String message) const;
    //! Print help on how to use the app
    void print_help() const;
};

#endif // IO_HANDLER_HPP
