cmake_minimum_required(VERSION 3.13)
project(orderbook)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")
include_directories(include)

find_package(pybind11)


pybind11_add_module(${PROJECT_NAME} MODULE main.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)
add_executable(test tests/test.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)
add_executable(txtreader inputs/TxtReader.cpp src/Order.cpp src/OrderBook.cpp src/PriceLevel.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC pybind11::module) 
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION .
)