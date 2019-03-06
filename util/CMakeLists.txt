add_library(
    util SHARED
    cnxdata.h
    common.h
    chatdata.h
    chatdata.cpp
    messagequeue.h
    messagequeue.cpp
    user.h
    user.cpp
    #threadsafelist.h
    #threadsafelist.cpp
    util.h
    util.cpp

)

#target_link_libraries(connection LINK_PUBLIC ${Boost_LIBRARIES} )
target_include_directories(util PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')
