cmake_minimum_required(VERSION 3.0)

project(atm_controller)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_library(atm_lib ${PROJECT_SOURCE_DIR}/src/atm.cpp)
add_library(bank_lib ${PROJECT_SOURCE_DIR}/src/bank.cpp)

add_executable(run_atm ${PROJECT_SOURCE_DIR}/tests/run_atm.cpp)
target_link_libraries(run_atm bank_lib atm_lib)
