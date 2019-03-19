add_library(
    connection SHARED
    cnx.cpp
    cnx.h
    connectionlist.cpp
    connectionlist.h
    connectionmanager.cpp
    connectionmanager.h
)

target_link_libraries(util PRIVATE connection)
target_include_directories(connection PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')
