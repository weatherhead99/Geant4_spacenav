project(Geant4_spacenav)
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

find_package(Geant4 COMPONENTS ui_all vis_all)
find_package(X11 REQUIRED)

include(${Geant4_USE_FILE})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(libspnav REQUIRED)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED QtGui)
find_package(Threads REQUIRED)

add_library(Geant4_spacenav src/libspnavpp.cpp src/SpacenavMessenger.cpp
src/G4X11Utils.cpp src/G4Spacenav.cpp src/SpacenavQtMessenger.cpp)
target_link_libraries(Geant4_spacenav PUBLIC libspnav::libspnav X11 ${Geant4_LIBRARIES} Threads::Threads Qt4::QtGui)
target_include_directories(Geant4_spacenav PUBLIC include ${Geant4_INCLUDE_DIRS})


add_executable(main main.cpp)
target_link_libraries(main Geant4_spacenav)
