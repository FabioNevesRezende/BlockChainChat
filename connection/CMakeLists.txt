add_library(
    connection SHARED
    cnx.cpp
    cnx.h
    connectionmanager.cpp
    connectionmanager.h
)

target_link_libraries(connection PUBLIC util)
target_include_directories(connection PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')
