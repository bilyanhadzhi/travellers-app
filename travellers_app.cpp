#include <cstring>
#include <cctype>
#include "travellers_app.hpp"
#include "date.hpp"

bool is_valid_img_filename(const char* filename);

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
        else if (command == COMMAND_MY_FRIENDS)
        {
            this->handle_command_my_friends();
        }
        else if (command == COMMAND_ADD_FRIEND)
        {
            this->handle_command_add_friend();
        }
        else if (command == COMMAND_HELP)
        {
            this->handle_command_help();
        }
        else if (command == COMMAND_EXIT)
        {
            this->database.save_destinations();
            this->database.save_user();
            this->io_handler.print_message(MESSAGE_EXIT);
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
    else
    {
        this->io_handler.print_success("User registered");
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
        std::cout << all_destinations[i] << "\n";
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

    this->io_handler.print_success("Destination added");
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

    const Vector<Trip> user_trips = this->database.get_curr_user()->get_trips();
    const int trips_count = user_trips.get_len();

    if (trips_count < 1)
    {
        this->io_handler.print_message("No trips");
        return;
    }

    for (int i = 0; i < trips_count; ++i)
    {
        std::cout << user_trips[i] << "\n";
    }
}

void TravellersApp::handle_command_add_trip()
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
            this->io_handler.print_message("'add_trip' is an interactive command. Just type in 'add_trip'");
        }
        return;
    }

    std::cin.ignore();
    if (!this->is_logged_in())
    {
        this->io_handler.print_not_logged_in();
        return;
    }

    Destination* found_destination = nullptr;
    int failed_tries = 0;

    String dest;
    do
    {
        if (failed_tries > 1)
        {
            std::cout << "Do you wish to go back? (y/n) ";
            char ans;
            std::cin >> ans;

            if (ans == 'y')
            {
                return;
            }
        }

        std::cout << "Enter destination: ";
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }

        dest.input(std::cin, true, '\n');
        found_destination = this->database.get_destination_by_name(dest.to_c_string());

        if (!found_destination)
        {
            this->io_handler.print_error("Destination does not exist");
            ++failed_tries;
        }
    }
    while (found_destination == nullptr);

    String start_date_string;
    Date start_date;

    bool date_is_set = false;
    failed_tries = 0;
    do
    {
        std::cin.ignore();
        int day, month, year;

        if (failed_tries > 1)
        {
            std::cout << "Do you wish to go back? (y/n) ";
            char ans;
            std::cin >> ans;
            std::cin.ignore();

            if (ans == 'y')
            {
                return;
            }
        }

        std::cout << "Enter start date: (YYYY-MM-DD): ";
        std::cin >> start_date_string;

        if (!start_date.is_valid_date_string(start_date_string.to_c_string()))
        {
            this->io_handler.print_message("Invalid date string");
            ++failed_tries;
            continue;
        }

        failed_tries = 0;
        if (!start_date.set_date(start_date_string.to_c_string()))
        {
            this->io_handler.print_message("Invalid date");
            ++failed_tries;
            continue;
        }
        else
        {
            date_is_set = true;
        }
    }
    while (!date_is_set);

    String end_date_string;
    Date end_date;

    date_is_set = false;
    failed_tries = 0;
    do
    {
        std::cin.ignore();
        int day, month, year;

        if (failed_tries > 1)
        {
            std::cout << "Do you wish to go back? (y/n) ";
            char ans;
            std::cin >> ans;
            std::cin.ignore();

            if (ans == 'y')
            {
                return;
            }
        }

        std::cout << "Enter end date: (YYYY-MM-DD): ";
        std::cin >> end_date_string;

        if (!end_date.is_valid_date_string(end_date_string.to_c_string()))
        {
            this->io_handler.print_message("Invalid date string");
            ++failed_tries;
            continue;
        }

        if (!end_date.set_date(end_date_string.to_c_string()))
        {
            this->io_handler.print_message("Invalid date");
            ++failed_tries;
            continue;
        }
        else if (end_date < start_date)
        {
            this->io_handler.print_message("End date cannot be earlier than start date");
            ++failed_tries;
            continue;
        }
        else
        {
            date_is_set = true;
        }
    }
    while (!date_is_set);

    int rating = -1;
    failed_tries = 0;
    do
    {
        if (failed_tries > 1)
        {
            std::cout << "Do you wish to go back? (y/n) ";
            char ans;
            std::cin >> ans;

            if (ans == 'y')
            {
                return;
            }
        }

        std::cout << "Enter rating: [1-5]: ";
        std::cin >> rating;

        if (rating < DEST_MIN_RATING || rating > DEST_MAX_RATING)
        {
            this->io_handler.print_error("Rating not valid");
            ++failed_tries;
        }
        std::cin.ignore();
    }
    while (rating < DEST_MIN_RATING || rating > DEST_MAX_RATING);

    String comment_string = "";

    std::cout << "Enter comment (leave empty for no comment): ";
    comment_string.input(std::cin, true, '\n');

    Comment comment(comment_string, this->database.get_curr_user()->get_username());

    bool photos_entered = false;
    Vector<String> photo_filenames;
    do
    {
        if (failed_tries > 1)
        {
            std::cout << "Do you wish to go back? (y/n) ";
            char ans;
            std::cin >> ans;

            if (ans == 'y')
            {
                return;
            }
        }

        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }

        std::cout << "Enter photo filenames (leave empty for no photos): ";
        this->io_handler.input_args(std::cin);

        photo_filenames = this->io_handler.get_args();
        const int photos_count = photo_filenames.get_len();

        failed_tries = 0;
        for (int i = 0; i < photos_count; ++i)
        {
            if (!is_valid_img_filename(photo_filenames[i].to_c_string()))
            {
                std::cout << "File \"" << photo_filenames[i] << "\" has invalid filename\n";
                ++failed_tries;
            }
        }

        if (failed_tries > 0)
        {
            continue;
        }
        photos_entered = true;
    }
    while (!photos_entered);

    Trip new_trip(found_destination->get_name(), start_date, end_date, rating, comment, photo_filenames);
    this->database.add_trip_curr_user(new_trip);
    found_destination->add_visit(rating);
    this->io_handler.print_success("Trip added");
}

// helper function
bool is_valid_img_filename(const char* filename)
{
    String extension;
    const int filename_len = strlen(filename);

    if (filename_len < 4)
    {
        return false;
    }

    // find beginning of extension
    int last_dot_index;
    int i = filename_len - 1;
    while (filename[i] != '.')
    {
        --i;
    }

    last_dot_index = i;

    for (i = last_dot_index + 1; i < filename_len; ++i)
    {
        extension += filename[i];
    }

    for (int j = 0; j < filename_len; ++j)
    {
        if (!isalpha(filename[j]) && filename[j] != '_')
        {
            if (filename[j] == '.' && j == last_dot_index)
            {
                continue;
            }
            return false;
        }
    }

    if (extension != "jpg" && extension != "jpeg" && extension != "png")
    {
        return false;
    }

    return true;
}

void TravellersApp::handle_command_my_friends()
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
            this->io_handler.print_message("No arguments needed");
        }
        return;
    }

    std::cin.ignore();
    if (!this->is_logged_in())
    {
        this->io_handler.print_not_logged_in();
        return;
    }

    Vector<String> user_friends_usernames = this->database.get_curr_user()->get_friends_usernames();
    const int user_friends_count = user_friends_usernames.get_len();

    if (user_friends_count < 1)
    {
        std::cout << "No friends :(\n";
        return;
    }

    for (int i = 0; i < user_friends_count; ++i)
    {
        std::cout << user_friends_usernames[i] << "\n";
    }
}

void TravellersApp::handle_command_add_friend()
{
    if (std::cin.peek() == '\n')
    {
        if (!this->is_logged_in())
        {
            this->io_handler.print_not_logged_in();
        }
        else
        {
            this->io_handler.print_usage(COMMAND_ADD_FRIEND, USAGE_ADD_FRIEND);
        }

        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->is_logged_in())
    {
        this->io_handler.print_not_logged_in();
        return;
    }

    if (!this->io_handler.check_number_of_arguments(1))
    {
        this->io_handler.print_usage(COMMAND_ADD_FRIEND, USAGE_ADD_FRIEND);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    User* found_user = this->database.get_user_by_username(arguments[0].to_c_string());

    if (!found_user)
    {
        this->io_handler.print_error("Could not find user");
        delete found_user;
        return;
    }
    else if (found_user->get_username() == this->database.get_curr_user()->get_username())
    {
        this->io_handler.print_error("You can't add yourself as a friend :)");
        delete found_user;
        return;
    }

    this->database.get_curr_user()->add_friend(found_user->get_username());
    this->io_handler.print_success("Friend added");
    delete found_user;

    return;
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
