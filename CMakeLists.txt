cmake_minimum_required(VERSION 3.14)

project(
    Shatar
    VERSION 0.1.0
    DESCRIPTION "Shatar chess"
    LANGUAGES CXX
)

add_executable(shatar_exe source/main.cpp source/Bitboard.cpp source/Bitboard.h)
add_executable(shatar::exe ALIAS shatar_exe)

set_property(TARGET shatar_exe PROPERTY OUTPUT_NAME shatar)

target_compile_features(shatar_exe PRIVATE cxx_std_20)
