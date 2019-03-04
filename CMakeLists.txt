CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/rshell.cpp
    src/normcommand.cpp
    src/testcommand.cpp
)

ADD_EXECUTABLE(test
    unit_test/unit_test.cpp
    src/rshell.cpp
    src/normcommand.cpp
    src/testcommand.cpp
)

TARGET_LINK_LIBRARIES(rshell gtest)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(rshell PRIVATE gtest_desable_pthreads = ON)
