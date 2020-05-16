cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)


project(8_lab)

string(APPEND CMAKE_CXX_FLAGS " -g -Wall -DBOOST_LOG_DYN_LINK")

include_directories(include)

find_package(Boost 1.65.1 COMPONENTS REQUIRED thread log log_setup)

add_executable(8_lab
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        )
target_include_directories(8_lab
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

include_directories(${Boost_INCLUDE_DIRS})
#target_link_libraries(tests GTest::main 8_lab)
target_link_libraries(8_lab Boost::log Boost::thread)
target_link_libraries(8_lab ${Boost_LIBRARIES})
link_directories("${Boost_Path}/installed/lib")