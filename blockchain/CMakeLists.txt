add_library(
    blockchain SHARED
    block.cpp
    block.h
    blockchain.cpp
    blockchain.h
)

target_link_libraries(blockchain PRIVATE util)

target_compile_definitions(blockchain PUBLIC DEBUG_VERSION)

target_include_directories(blockchain PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')