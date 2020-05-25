#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Commands
#define COMMAND_REGISTER        "register"
#define COMMAND_LOG_IN          "log_in"
#define COMMAND_DESTINATIONS    "destinations"
#define COMMAND_MY_TRIPS        "my_trips"
#define COMMAND_ADD_TRIP        "add_trip"
#define COMMAND_HELP            "help"
#define COMMAND_EXIT            "exit"

// Commands usage
#define USAGE_REGISTER          "<username> <email> <password>"
#define USAGE_LOG_IN            "<username> <password>"

// File names
#define DB_SUBDIR                   "db/"
#define DB_USERS_SUBDIR             "db/users/"
#define DB_FILENAME_USERS           "users.db"
#define DB_FILENAME_DESTINATIONS    "destinations.db"
#define DB_EXTENSION                ".db"

// Vector
#define VECTOR_DEFAULT_CAPACITY 16

// General buffer size
#define BUFFER_SIZE 256

// Validation constants
#define MAX_USERNAME_LEN 64
#define MIN_PASSWORD_LEN 10
#define MAX_PASSWORD_LEN 256
#define MIN_EMAIL_LEN 5
#define MAX_EMAIL_LEN 256

#endif // CONSTANTS_HPP
