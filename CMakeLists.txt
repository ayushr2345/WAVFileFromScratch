cmake_minimum_required(VERSION 3.22)
project(WAVFileFromScratch)

set (CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
    WAVFileFromScratch/WAVFileFromScratch.cpp
    WAVFileFromScratch/SineWave.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
