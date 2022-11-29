cmake_minimum_required(VERSION 3.5)

project(let3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# флаг, который подключает тесты к проекту
set(ENABLE_UNIT_TESTS ON)

set(TEST_DIR Tests)
set(FILES
    job.h
    job.cpp
)

find_package(Threads REQUIRED)

add_executable(let3 main.cpp ${FILES})

target_link_libraries(${PROJECT_NAME}
    Threads::Threads
)

if (ENABLE_UNIT_TESTS)

    include(FetchContent)
    include(GoogleTest)
    enable_testing()

    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        release-1.12.1
    )

    FetchContent_MakeAvailable(googletest)

    set(TEST_SOURCES
        ${TEST_DIR}/tests.cpp
        ${FILES}
    )

    set(TEST_PROJECT_NAME let3-test)

    find_package(Threads REQUIRED)

    add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES})

    target_link_libraries(${TEST_PROJECT_NAME}
        PRIVATE gtest_main
        Threads::Threads
    )

endif()
