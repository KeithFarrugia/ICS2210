cmake_minimum_required(VERSION 3.0.0)
project(ICS2210_CourseWork VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
set(DATA_STRUCTURES_HEADER
    AVL/Avl.h
    RB/RedBlack.h
    SkipLists/SkipList.h
)
set(DATA_STRUCTURES_SOURCE
    AVL/Avl.cpp
    AVL/AvlRotations.cpp
    AVL/AvlStatistics.cpp

    RB/RedBlack.cpp
    RB/RedBlackRotation.cpp
    RB/RedBlackConflicts.cpp
    RB/RedBlackStatistics.cpp

    SkipLists/SkipList.cpp
    SkipLists/SkipListStatistics.cpp
)

add_library(DATA_STRUCTURES_LIB ${DATA_STRUCTURES_HEADER} ${DATA_STRUCTURES_SOURCE})

set(SOURCE_FILES main.cpp)
add_executable(ICS2210_CourseWork ${SOURCE_FILES})
target_link_libraries(ICS2210_CourseWork DATA_STRUCTURES_LIB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
