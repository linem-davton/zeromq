
set(EXENAME "rep_server")

add_executable(${EXENAME} server.cpp)


# Find ZeroMQ if not found raise error
find_package(ZeroMQ REQUIRED)

# Add ZeroMQ include directory to compiler include directories
include_directories(${ZeroMQ_INCLUDE_DIR})

# Link ZeroMQ library to the executable Done by linker 
target_link_libraries(${EXENAME} ${ZeroMQ_LIBRARY})

# Install the executable to bin directory (usr/local/bin)
# Testing purpose only
install(TARGETS ${EXENAME} DESTINATION bin)
