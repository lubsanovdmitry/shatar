cmake_minimum_required(VERSION 3.14)

project(
        Shatar
        VERSION 0.1.0
        DESCRIPTION "Shatar chess"
        HOMEPAGE_URL "https://github.com/lubsanovdmitry/shatar"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_library(
        rang_lib OBJECT
        include/rang.hpp
)

set_target_properties(rang_lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
        rang_lib #${warning_guard}
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(rang_lib PUBLIC cxx_std_20)

add_executable(shatar_exe
        source/main.cpp
        source/Bitboard.cpp source/Bitboard.h
        source/Board.cpp source/Board.h
        source/Hash.cpp source/Hash.h
        source/Players.h
        source/Move.h source/Move.cpp
        source/Position.cpp source/Position.h
        source/MoveMasks.h
        source/PseudoLegalMoveMaskGen.cpp source/PseudoLegalMoveMaskGen.h source/MoveList.cpp source/MoveList.h source/LegalMoveGen.cpp source/LegalMoveGen.h source/Static.cpp source/Static.h source/MoveSort.cpp source/MoveSort.h source/HashTable.cpp source/HashTable.h source/AI.cpp source/Human.cpp)

add_executable(shatar::exe ALIAS shatar_exe)

set_property(TARGET shatar_exe PROPERTY OUTPUT_NAME shatar)

target_compile_features(shatar_exe PRIVATE cxx_std_20)

target_link_libraries(shatar_exe PRIVATE rang_lib)
target_include_directories(shatar_exe PRIVATE "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")