cmake_minimum_required(VERSION 3.5)

project(let3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads)

add_executable(let3 main.cpp job.h job.cpp)

target_link_libraries(${PROJECT_NAME}
    Threads::Threads
)
