cmake_minimum_required(VERSION 3.14)
project(blueROV LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

add_executable(blueROV
    src/main.cpp
    src/mapCreation.cpp
    src/spawnConfig.cpp
    src/mapVisualizer.cpp
)

target_include_directories(blueROV PRIVATE
    src
)

# SFML
find_package(SFML 3 CONFIG QUIET COMPONENTS Graphics Window System)
if (SFML_FOUND)
    target_link_libraries(blueROV PRIVATE SFML::Graphics SFML::Window SFML::System)
else()
    find_package(SFML 2 CONFIG REQUIRED COMPONENTS graphics window system)
    if (TARGET SFML::Graphics)
        target_link_libraries(blueROV PRIVATE SFML::Graphics SFML::Window SFML::System)
    else()
        target_link_libraries(blueROV PRIVATE sfml-graphics sfml-window sfml-system)
    endif()
endif()

# GDAL
# GDAL
find_package(GDAL REQUIRED)
if(GDAL_FOUND)
    target_include_directories(blueROV PRIVATE ${GDAL_INCLUDE_DIRS})
    target_link_libraries(blueROV PRIVATE ${GDAL_LIBRARIES})
endif()