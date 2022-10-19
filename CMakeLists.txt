cmake_minimum_required(VERSION 3.23)
project(Grafen)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Grafen main.cpp engine.h grafen/Graaf.cpp grafen/Graaf.h)

target_link_libraries(Grafen PRIVATE sfml-graphics)
target_compile_features(Grafen PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Grafen POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Grafen> $<TARGET_FILE_DIR:Grafen> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Grafen)
