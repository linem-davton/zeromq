# Global Cmake file for the project

cmake_minimum_required(VERSION 3.0)

# For organization only doesn't affect compilation
project(MQ_Application)

# Set Global C++ standard to 20 and forced to true
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include subdirectories
add_subdirectory(rep_server)
add_subdirectory(pub_server)