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
    util.h
    util.cpp
    threadsafelist.h
    threadsafelist.cpp

)

target_include_directories(util PUBLIC '${CMAKE_CURRENT_SOURCE_DIR}')
