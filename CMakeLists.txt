# cmake_minimum_required(VERSION 3.4...3.18)
# project(cmake_example)

# add_library(mymath STATIC src/mymath.cpp)
# set_target_properties(mymath PROPERTIES POSITION_INDEPENDENT_CODE ON)

# add_subdirectory(pybind11)
# pybind11_add_module(cmake_example src/binder.cpp)
# target_link_libraries(cmake_example PRIVATE mymath)

cmake_minimum_required(VERSION 3.5...3.27)
project(Client)

add_subdirectory(pybind11 REQUIRED)  # or `add_subdirectory(pybind11)`

add_executable(Client src/Client/client_connection.cpp src/Client/client_main.cpp)
target_link_libraries(Client PRIVATE pybind11::embed)