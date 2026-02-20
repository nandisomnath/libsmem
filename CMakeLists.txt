cmake_minimum_required(VERSION 4.2)

project(libsmem
VERSION "0.0.1"
DESCRIPTION "a project for c memory management" 
)

include_directories("include")

add_executable(test
src/main.c
)