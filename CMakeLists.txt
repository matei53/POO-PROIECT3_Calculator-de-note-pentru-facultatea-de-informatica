cmake_minimum_required(VERSION 3.28)
project("POO-PROIECT3_Calculator-de-note-pentru-facultatea-de-informatica")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
