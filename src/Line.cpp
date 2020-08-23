/*
 * Line.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Line.h"
#include <iostream>
namespace mpal {

Line::Line(Point p1, Point p2) :
		point_start(p1), point_end(p2) {

}

Line::~Line() {

}

void Line::set_pos(int unsignedInt, int unsignedInt1) {
}

void Line::move(int unsignedInt, int unsignedInt1) {
}

std::vector<std::pair<int, int>> Line::draw() {
	std::vector<std::pair<int, int>> vec;

	int dx;
	int dy;
	int i;
	int xinc;
	int yinc;
	int cumul;
	int x;
	int y;

	x = point_start.getPosX();
	y = point_start.getPosY();
	dx = point_end.getPosX() - point_start.getPosX();
	dy = point_end.getPosY() - point_start.getPosY();
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	vec.push_back(std::make_pair(x, y));
	if (dx > dy) {
		cumul = dx / 2;
		for (i = 1; i <= dx; i++) {
			x += xinc;
			cumul += dy;
			if (cumul >= dx) {
				cumul -= dx;
				y += yinc;
			}
			vec.push_back(std::make_pair(x, y));
		}
	} else {
		cumul = dy / 2;
		for (i = 1; i <= dy; i++) {
			y += yinc;
			cumul += dx;
			if (cumul >= dy) {
				cumul -= dy;
				x += xinc;
			}
			vec.push_back(std::make_pair(x, y));
		}
	}

	return (vec);
}

double Line::get_dist() {
	int distX = point_start.getPosX() - point_end.getPosX();
	int distY = point_start.getPosY() - point_end.getPosY();
	float distance = sqrt( (distX*distX) + (distY*distY) );
	return (distance);
}

} /* namespace mpal */
