cmake_minimum_required(VERSION 3.20)
project(test_pq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PostgreSQL_ADDITIONAL_VERSIONS 17)
set( SOURCES
    main.cpp
    db_customer.cpp
)
set( HEADERS
    db_customer.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_subdirectory("C:\\...\\libpqxx" build-pqxx)

target_compile_features(test_pq PRIVATE cxx_std_17)
target_link_libraries(test_pq PRIVATE pqxx)

# libpqxx
# Доделываю...Прошу понять и дать немного времени!:)