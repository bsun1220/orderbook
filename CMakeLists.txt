cmake_minimum_required(VERSION 3.13)
project(orderbook)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")
include_directories(include)

add_executable(${PROJECT_NAME} main.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)
add_executable(test tests/test.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)
add_executable(txtreader inputs/TxtReader.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)