cmake_minimum_required (VERSION 3.15.3)
project (NeuralNetwork)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")     
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -Ofast -flto -march=native -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -g -pedantic -fsanitize=address --coverage -pg")
set(CMAKE_CXX_FLAGS_TESTS "${CMAKE_CXX_FLAGS_TEST} -std=c++17 -g -pedantic -fsanitize=address -D_TESTS")

set(SHARED_INCLUDE_DIR libs src/utils
                            src/matrix)

add_library(op_overloading OBJECT)
target_sources(op_overloading
    PRIVATE "src/utils/op_overloading.cc"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/op_overloading.hh"
)
target_compile_options(op_overloading PRIVATE -Wall -Wextra -Werror)
target_link_libraries(op_overloading PUBLIC "")
target_include_directories(op_overloading PUBLIC ${SHARED_INCLUDE_DIR})

add_library(matrix OBJECT)
target_sources(matrix
    PRIVATE "src/matrix/matrix.cc"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/src/matrix/matrix.hh"
)
target_compile_options(matrix PRIVATE -Wall -Wextra -Werror)
target_link_libraries(matrix PUBLIC "")
target_include_directories(matrix PUBLIC ${SHARED_INCLUDE_DIR})

add_library(main OBJECT)
target_sources(main
    PRIVATE "src/main/main.cc"
)
target_compile_options(main PRIVATE -Wall -Wextra -Werror)
target_include_directories(main PUBLIC ${SHARED_INCLUDE_DIR})

add_library(test OBJECT)
target_sources(test
    PRIVATE "src/test/test.cc"
)
target_compile_options(test PRIVATE -I$(CATCH_SINGLE_INCLUDE) -Wall -Wextra -Werror)
target_include_directories(test PUBLIC ${SHARED_INCLUDE_DIR})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Tests")
    add_executable(Tests)
    target_link_libraries(Tests PRIVATE op_overloading
                                        matrix
                                        test)
else()
    add_executable(Raytracer)
    target_link_libraries(Raytracer PRIVATE op_overloading
                                            matrix
                                            main)
endif()
