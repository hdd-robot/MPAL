/*
 * test_d_nav.cpp
 *
 *  Created on: 20 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LIDAR

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <string>
#include "Environment.h"
#include "EnvironmentCell.h"
#include "EnvironmentContinue.h"
#include "Lidar.h"

using namespace mpal;

BOOST_AUTO_TEST_SUITE (test_lidar)

struct LidarTest : Lidar {

	LidarTest(Environment* env, int px, int py, int rad):Lidar(env, px, py,  rad)  {}

	~LidarTest() {
		BOOST_TEST_MESSAGE( "teardown Env" );

	}


};




BOOST_AUTO_TEST_SUITE_END()











