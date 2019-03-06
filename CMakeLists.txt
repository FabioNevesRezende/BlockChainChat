cmake_minimum_required(VERSION 3.13)
project(BlockChainChat VERSION 1.0.0) 

set (CMAKE_CXX_STANDARD 17)

find_package(Boost 1.62 COMPONENTS program_options REQUIRED system)
include_directories( ${Boost_INCLUDE_DIR} )

add_subdirectory(util)
add_subdirectory(application)
add_subdirectory(connection)
add_subdirectory(blockchain)

add_executable(BlockChainChat main.cpp)

target_link_libraries(BlockChainChat LINK_PUBLIC ${Boost_LIBRARIES} )
target_link_libraries(BlockChainChat PRIVATE util)
target_link_libraries(BlockChainChat PRIVATE application)
target_link_libraries(BlockChainChat PRIVATE connection)
target_link_libraries(BlockChainChat PRIVATE blockchain)