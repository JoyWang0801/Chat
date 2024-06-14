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

# include(FetchContent)
# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
# FetchContent_MakeAvailable(json)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

add_executable(Client src/Client/client_connection.cpp src/Client/client_main.cpp src/Client/client_ui.cpp)
target_link_libraries(Client PRIVATE pybind11::embed)
target_link_libraries(Client
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
# target_link_libraries(Client PRIVATE nlohmann_json::nlohmann_json)

project(Server)

add_executable(Server src/Server/server.cpp)