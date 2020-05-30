#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define SHELL_PROMPT            "(traveller's app) $ "

// Commands
#define COMMAND_REGISTER        "register"
#define COMMAND_LOG_IN          "log_in"
#define COMMAND_DESTINATIONS    "destinations"
#define COMMAND_ADD_DESTINATION "add_destination"
#define COMMAND_MY_TRIPS        "my_trips"
#define COMMAND_ADD_TRIP        "add_trip"
#define COMMAND_MY_FRIENDS      "my_friends"
#define COMMAND_ADD_FRIEND      "add_friend"
#define COMMAND_HELP            "help"
#define COMMAND_EXIT            "exit"

// Commands usage
#define USAGE_REGISTER          "<username> <email> <password>"
#define USAGE_LOG_IN            "<username> <password>"
#define USAGE_ADD_DESTINATION   "<name> (e.g. 'add_destination Yosemite', 'add_destination \"Sofia, Bulgaria\"'"
#define USAGE_ADD_FRIEND        "<name>"

#define MESSAGE_EXIT            "Bye! :)"

// File names
#define DB_SUBDIR                   "db/"
#define DB_USERS_SUBDIR             "db/users/"
#define DB_FILENAME_USERS           "users.db"
#define DB_FILENAME_DESTINATIONS    "destinations.db"
#define DB_EXTENSION                ".db"

// Destination
#define DEST_MIN_RATING 1
#define DEST_MAX_RATING 5

// Vector
#define VECTOR_DEFAULT_CAPACITY 16

// General buffer size
#define BUFFER_SIZE 256

// Characters to print before truncating long strings (like a description)
#define PRINT_MAX_DESC_LEN 50
#define PRINT_MAX_PHOTO_NAMES_LEN 30

// Validation constants
#define MAX_USERNAME_LEN 64
#define MIN_PASSWORD_LEN 10
#define MAX_PASSWORD_LEN 256
#define MIN_EMAIL_LEN 5
#define MAX_EMAIL_LEN 256

#endif // CONSTANTS_HPP
