set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0 )

link_directories(${GTKMM_LIBRARY_DIRS} )
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} ) 

file(GLOB SOURCES_FILES "*.cpp")
file(GLOB HEADERS_FILES "*.h")


# exe
add_executable(mpal ${SOURCES_FILES} ${HEADERS_FILES})
target_link_libraries(mpal ${GTKMM_LIBRARIES} ${Boost_LIBRARIES} gvc cgraph)

