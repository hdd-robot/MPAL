/*
 * Point.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Point.h"

namespace mpal {

Point::Point(int x, int y) :
		pos_x(x), pos_y(y) {
}

Point::~Point() {
}

void Point::set_pos(int pos_x, int pos_y) {
}

void Point::move(int pos_x, int pos_y) {
}

std::vector<std::pair<int, int>> Point::draw() {
	std::vector<std::pair<int, int>> vec;
	vec.push_back(std::make_pair(getPosX(), getPosY()));
	return vec;
}

} /* namespace mpal */
