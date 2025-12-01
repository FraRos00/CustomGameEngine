cmake_minimum_required(VERSION 3.16)
project(game LANGUAGES CXX)

# -------------------------------------
# Default build: Debug
# -------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()



# Esporta compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------
# Impostazioni compilatore
# -------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

# Debug flags equivalenti al Makefile
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

# Release flags 
set(CMAKE_CXX_FLAGS_RELEASE "-WAll -Wextra -O2")

include_directories(include)

# Output eseguibile con nome dipendente dal sistema
if (WIN32)
    set(BIN_NAME "game.exe")
else()
    set(BIN_NAME "game")
endif()

# -------------------------------------
# Sorgenti
# -------------------------------------

file(GLOB_RECURSE SOURCES "src/*.cpp")

# -------------------------------------
# Raylib: trova o installa automaticamente
# -------------------------------------
find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message(WARNING "Raylib non trovato nel sistema. Lo scarico via FetchContent.")
    # include(FetchContent)
    # FetchContent_Declare(
    #     raylib
    #     GIT_REPOSITORY https://github.com/raysan5/raylib.git
    #     GIT_TAG 5.5
    # )
    # FetchContent_MakeAvailable(raylib)
else()
    message(STATUS "Raylib trovato nel sistema.")
endif()

# -------------------------------------
# Crea l’eseguibile
# -------------------------------------

add_executable(${BIN_NAME} ${SOURCES})

# -------------------------------------
# Link delle librerie
# -------------------------------------

if (WIN32)
    target_link_libraries(${BIN_NAME}
        raylib
        opengl32
        gdi32
        winmm
        # waylandscale
    )
else()
    target_link_libraries(${BIN_NAME}
        raylib
        glfw
        m
        dl
        pthread
        rt
        # waylandscale
        # wayland-client
    )
endif()

# Aggiungi directory lib/ (equivalente a -Llib)
target_link_directories(${BIN_NAME} PRIVATE lib)
