CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(test
    src/main.cpp
    src/rshell.cpp
    src/and.cpp
    src/command.cpp
    src/connector.cpp
    src/or.cpp
    src/semiColon.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_desable_pthreads = ON)
