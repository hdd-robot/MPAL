cmake_minimum_required(VERSION 3.0.2)

project(MPAL)

enable_language(CXX)

include(CTest)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)


find_package(Boost  REQUIRED COMPONENTS unit_test_framework)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0 )

link_directories(${GTKMM_LIBRARY_DIRS} )
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} ) 



add_subdirectory(src)
#add_subdirectory(test)
