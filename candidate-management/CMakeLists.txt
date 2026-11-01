cmake_minimum_required(VERSION 3.10)

project(Candidate_Management_System)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app
    main.cpp
    Candidate.cpp
    LinkedList.cpp
    HashTable.cpp
    CandidateManager.cpp
    Sorter.cpp
    RoomAllocator.cpp
    Utils.cpp
)

# Copy input.txt vao build directory de app luon tim duoc file
configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
