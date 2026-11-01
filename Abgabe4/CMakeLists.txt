cmake_minimum_required(VERSION 3.16)
project(Uebung04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Jede Datei hat ein eigenes main() -> eigenes Executable
foreach(prog main move_demo moved_from no_copy)
    add_executable(Uebung04_${prog} ${prog}.cpp channel.hpp)
    target_link_libraries(Uebung04_${prog} PRIVATE Threads::Threads)
endforeach()

# Optional: Compile-Fehler-Demos für gelöschte Copy-Konstruktoren
# (absichtlich NICHT kompilierbar, daher nur auf Anfrage)
option(UEBUNG04_COPY_DEMOS "Baue no_copy mit COPY_SENDER/COPY_RECEIVER (schlägt fehl)" OFF)
if(UEBUNG04_COPY_DEMOS)
    add_executable(Uebung04_no_copy_sender no_copy.cpp)
    target_compile_definitions(Uebung04_no_copy_sender PRIVATE COPY_SENDER)
    add_executable(Uebung04_no_copy_receiver no_copy.cpp)
    target_compile_definitions(Uebung04_no_copy_receiver PRIVATE COPY_RECEIVER)
endif()
