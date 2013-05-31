cmake_minimum_required (VERSION 2.6) 
 
set (PROJECT redundant-code) 
 
project (${PROJECT}) 
 
set (HEADERS 
	Combination.h)
 
set (SOURCES 
	main.cpp
    Combination.cpp) 
 
add_executable (${PROJECT} ${SOURCES})