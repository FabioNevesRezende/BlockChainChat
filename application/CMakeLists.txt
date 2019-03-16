add_library(
    application SHARED
    application.cpp
    application.h
)

target_include_directories(application PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')
