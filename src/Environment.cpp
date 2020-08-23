/*
 * Environnement.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Environment.h"

namespace mpal {

Environment::Environment(int pWidth, int pHeight) :
		width(pWidth), height(pHeight) {

}

Environment::~Environment() {
	for (auto &elem : lst_obstacles) {
		delete elem;
	}
}

void Environment::draw_outline() {
	Obstacle *obs = new Line(Point(0, 0), Point(0, width - 1));
	add_obstacle(obs);
}

bool Environment::add_obstacle(Obstacle *obs) {
	Obstacle *cp_obs = obs->cloner();
	lst_obstacles.push_back(cp_obs);
	std::vector<std::pair<int, int>> lst_points = obs->draw();

	return true;
}

bool Environment::set_robot_pos(int x, int y) {
	robot_pos_x = x;
	robot_pos_y = y;
	return true;
}

bool Environment::set_start_pos(int x, int y) {
	start_pos_x = x;
	start_pos_y = y;
	return true;
}

bool Environment::set_goal_pos(int x, int y) {
	goal_pos_x = x;
	goal_pos_y = y;
	return true;
}

} /* namespace mpal */
