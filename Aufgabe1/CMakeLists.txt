cmake_minimum_required(VERSION 3.16)

project(Aufgabe1 LANGUAGES CXX)

add_executable(Aufgabe1
    main.cpp
    1/nils_weberruss.cpp
    2/analyze.cpp
)

target_compile_features(Aufgabe1 PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(Aufgabe1 PRIVATE /utf-8)
endif()
