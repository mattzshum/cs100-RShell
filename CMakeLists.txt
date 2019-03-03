CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE( test
    main.cpp
    rshell.cpp
    normcommand.cpp
    testcommand.cpp
)

ADD_EXECUTABLE( run
    unit_test.cpp
    rshell.cpp
    normcommand.cpp
    testcommand.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(run gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_desable_pthreads = ON)
