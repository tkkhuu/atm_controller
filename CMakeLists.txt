cmake_minimum_required(VERSION 3.0)

project(atm_controller)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# add_library(atm_lib ${PROJECT_SOURCE_DIR}/src/atm.cpp)
add_library(bank_lib ${PROJECT_SOURCE_DIR}/src/bank.cpp)

add_executable(check_balance ${PROJECT_SOURCE_DIR}/tests/check_balance.cpp)
target_link_libraries(check_balance bank_lib)
