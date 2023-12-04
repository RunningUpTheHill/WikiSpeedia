cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_CXX_STANDARD 17)
project(WikiSpeedia)

set(INCLUDE_PATHS /usr/local/include /usr/local/Cellar/asio/1.28.1/include)
add_executable(WikiSpeedia wiki_speedia_backend/main.cpp
        wiki_speedia_backend/AdjacencyList.h
        wiki_speedia_backend/crow_all.h
        )


target_include_directories(WikiSpeedia PUBLIC ${INCLUDE_PATHS})

set_target_properties(WikiSpeedia PROPERTIES
        LINK_FLAGS "-pthread"
        )