cmake_minimum_required(VERSION 3.0.0)
project(travellers_app VERSION 0.1.0)

include(CTest)
enable_testing()

link_libraries(bcrypt)

set(Sources
    main.cpp
    lib/string.cpp
    destination.cpp
    trip.cpp
    user.cpp
    date.cpp
    database.cpp
    io_handler.cpp
    travellers_app.cpp
)

set(Headers
    constants.hpp
    lib/string.hpp
    lib/vector.hpp
    destination.hpp
    trip.hpp
    user.hpp
    date.hpp
    database.hpp
    io_handler.hpp
    travellers_app.hpp
)

add_executable(travellers_app ${Sources} ${Headers})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
