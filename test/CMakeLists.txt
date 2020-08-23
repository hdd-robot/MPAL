

find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0 )

link_directories(${GTKMM_LIBRARY_DIRS} )
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} ) 

include_directories(../src)


file(GLOB TEST_HEADER_FILES    
	../src/Algo*.h
	../src/Environment*.h
	../src/Cell*.h
	../src/Obstacles.h
	../src/Graph.h
	../src/Point.h
	../src/Line.h
	../src/Lidar.h
	../src/Cercle.h
)


file(GLOB SOURCES_FILES    
	../src/Algo*.cpp
	../src/Environment*.cpp
	../src/Cell.cpp
	../src/Obstacle.cpp
	../src/Graph.cpp
	../src/Point.cpp
	../src/Line.cpp
	../src/Lidar.cpp
	../src/Cercle.cpp
)





# tests
add_definitions(-DBOOST_ALL_DYN_LINK)
 
enable_testing()


add_executable(algo_d_nav_exe ${TEST_SOURCES_FILES} ${TEST_HEADER_FILES} ${SOURCES_FILES} test_d_nav.cpp)
target_link_libraries(algo_d_nav_exe ${Boost_LIBRARIES} )
add_test(Algo_D_PATH_TEST algo_d_nav_exe)


add_executable(lidar_exe ${TEST_SOURCES_FILES} ${TEST_HEADER_FILES} ${SOURCES_FILES} test_lidar.cpp)
target_link_libraries(lidar_exe ${Boost_LIBRARIES} )
add_test(LIDAR_TEST lidar_exe)


add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

        
        
        
        
        