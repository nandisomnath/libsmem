cmake_minimum_required(VERSION 4.2)

project(libsmem
VERSION "0.0.1"
DESCRIPTION "a project for c memory management" 
)

include_directories("include")

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE "include")

add_executable(test
src/main.c
)