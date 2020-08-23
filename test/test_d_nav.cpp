/*
 * test_d_nav.cpp
 *
 *  Created on: 20 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Algo_D_PATH

#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE (test_d_nav)

BOOST_AUTO_TEST_CASE (test1str) {
	std::string s;
	BOOST_CHECK(s.size() == 0);
}

BOOST_AUTO_TEST_CASE (test2str) {
	std::string s;
	s = "hello world";
	BOOST_REQUIRE_EQUAL('h', s[0]);
}

BOOST_AUTO_TEST_SUITE_END()

