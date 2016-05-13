cmake_minimum_required(VERSION 3.1)
project(Queues)
set(CMAKE_CXX_STANDARD 11)
# include(FindSoil.cmake)

#########################################################
# Fix fedoras fucked up libs
#########################################################
# set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib64)


#########################################################
# Include Files
#########################################################
file(GLOB queues_src
    src/*.hpp
    src/*.h
    src/*.cpp
)

# file(GLOB queues_src
    # src/Tree.h
    # src/Tree.cpp
    # src/main.cpp
# )


add_executable(asd ${queues_src})

########################################################
# Linking & stuff
#########################################################

# create the program "test"
# target_link_libraries(asd ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} DevIL ILU ILUT)
