cmake_minimum_required(VERSION 3.11)
project(ZombieShooter)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_compile_options(-Wall -Wextra)

add_executable(ZombieShooter src/main.cpp
        src/Bullet.h src/Bullet.cpp
        src/Enemies.h src/Enemies.cpp
        src/GameBoard.h src/GameBoard.cpp
        src/Movable.h src/Movable.cpp
        src/Player.h src/Player.cpp
        src/SFMLGame.cpp src/SFMLGame.h)

if (UNIX)
    set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULES_PATH})
    set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
endif(UNIX)

if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML/")
endif(WIN32)


find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(ZombieShooter sfml-graphics sfml-audio sfml-system sfml-window)