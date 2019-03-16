CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES (
    src
    $ {CMAKE_SOURCE_DIR}/assignment-cs-100-darrien-christian/src
)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/rshell.cpp
    src/normcommand.cpp
    src/testcommand.cpp
)

ADD_EXECUTABLE(test
    unit_tests/unit_test.cpp
    src/rshell.cpp
    src/normcommand.cpp
    src/testcommand.cpp
)


TARGET_LINK_LIBRARIES(test gtest)
