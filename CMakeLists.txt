cmake_minimum_required(VERSION 3.31)
project(EDAPROYECTO_02)

set(CMAKE_CXX_STANDARD 20)

add_executable(EDAPROYECTO_02 main.cpp baseDeDatos.cpp
        HashTable.cpp MaxHeap.cpp AVLTree.cpp RBTree.cpp)
