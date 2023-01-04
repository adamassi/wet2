# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.0.0)
project(wet2_DS_winter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")

add_executable(wet2_DS_winter main23a2.cpp UnionFind.cpp UnionFind.h dynamicArr.h HashTable.h exceptions.h GenericNode.h RankAvlTree.h Player.cpp Player.h  Team.h Team.cpp wet2util.h worldcup23a2.h worldcup23a2.cpp )