cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME hash_chain)

add_executable(${TARGET_NAME}
        main.cpp
        HashTable.cpp
        Reader.cpp
)

# чтобы #include "Reader.h" и "HashTable.h" находились
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)