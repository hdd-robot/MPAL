/*
 * Environnement.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "EnvironmentCell.h"

namespace mpal {

EnvironmentCell::EnvironmentCell(int pWidth, int pHeight) :
		Environment(pWidth, pHeight) {

	board.resize(pHeight, pWidth);
	for (int i = 0; i < board.size1(); i++) {
		for (int j = 0; j < board.size2(); j++) {
			board(i, j).set_free();
			board(i, j).setPosX(j);
			board(i, j).setPosY(i);
		}
	}
}

EnvironmentCell::~EnvironmentCell() {

}

std::ostream& operator <<(std::ostream &param, const EnvironmentCell &env) {
	param << env.board;
	return (param);
}

void EnvironmentCell::print_board() {
	for (int i = 0; i < board.size1(); i++) {
		for (int j = 0; j < board.size2(); j++) {
			if (board(i, j).getCellType() == CellType::FREE) {
				std::cout << board(i, j).printStatus();
			} else {

				std::cout << board(i, j).printType();
			}

		}
		std::cout << std::endl;
	}
}

void EnvironmentCell::print_board_debug() {
	for (int i = 0; i < board.size1(); i++) {
		for (int j = 0; j < board.size2(); j++) {
			std::cout << board(i, j).print_debug();
		}
		std::cout << std::endl;
	}
}

bool EnvironmentCell::add_obstacle(Obstacle *obs) {
	Obstacle *cp_obs = obs->cloner();
	lst_obstacles.push_back(cp_obs);
	std::vector<std::pair<int, int>> lst_points = obs->draw();
	for (auto &row : lst_points) {
		board(row.second, row.first).set_obstcale(cp_obs);
	}

	return true;
}

bool EnvironmentCell::set_robot_pos(int x, int y) {
	if (board(y, x).is_free()) {
		board(y, x).set_robot();
		robot_pos_x = x;
		robot_pos_y = y;
		return true;
	}
	return false;
}

bool EnvironmentCell::set_start_pos(int x, int y) {
	if (board(y, x).is_free()) {
		board(y, x).set_start();
		start_pos_x = x;
		start_pos_y = y;
		return true;
	}
	return false;
}

void EnvironmentCell::draw_outline() {
}

bool EnvironmentCell::set_goal_pos(int x, int y) {
	if (board(y, x).is_free()) {
		board(y, x).set_goal();
		goal_pos_x = x;
		goal_pos_y = y;
		return true;
	}
	return false;
}

Cell& EnvironmentCell::getCellAt(int i, int j) {
	return board(j, i);
}

} /* namespace mpal */
