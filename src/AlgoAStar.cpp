/*
 * AlgoAStar.cpp
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "AlgoAStar.h"
#include <iostream>  // todo : remove
#include <unistd.h>  // todo : remove

namespace mpal {

AlgoAStar::AlgoAStar(EnvironmentCell *env) :
		AlgoCellBased(env) {
	algoName = AlgoType::ASTAR;
}

AlgoAStar::~AlgoAStar() {

}

bool AlgoAStar::init() {
	directions = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { -1, -1 },
			{ 1, 1 }, { -1, 1 }, { 1, -1 } };

	for (unsigned i = 0; i < environment->getWidth(); ++i) { // Y axe
		for (unsigned j = 0; j < environment->getHeight(); ++j) { // X axe
			environment->getCellAt(i, j).setGCost(std::numeric_limits<double>::infinity());
			environment->getCellAt(i, j).setHCost(std::numeric_limits<double>::infinity());
			environment->getCellAt(i, j).setFCost(std::numeric_limits<double>::infinity());
			environment->getCellAt(i, j).setPred(nullptr);
			environment->getCellAt(i, j).setCellStatus(CellStatus::UNEXPLORED);
		}
	}

	Cell &start_cell = environment->getCellAt(environment->getStartPosX(),
			environment->getStartPosY());
	start_cell.setGCost(0);
	start_cell.setHCost(
			calculateHValue(environment->getStartPosX(),
					environment->getStartPosY()));
	start_cell.setFCost(start_cell.getHCost() + start_cell.getGCost());
	start_cell.setPred(&start_cell);

	path.clear();
	close_list.clear();
	open_list.clear();
	open_list.push_back(&start_cell);
	notify();
	return (true);

}

bool AlgoAStar::isValid(int pos_x, int pos_y) {
	return ((pos_x >= 0) && (pos_x < environment->getWidth()) && (pos_y >= 0)
			&& (pos_y < environment->getHeight()));
}

bool AlgoAStar::isUnBlocked(int pos_x, int pos_y) {
	if (environment->getCellAt(pos_x, pos_y).getCellType()
			== CellType::OBSTACLE)
		return (false);
	return (true);
}

bool AlgoAStar::isDestination(int pos_x, int pos_y) {
	if ((environment->getCellAt(environment->getGoalPosX(),
			environment->getGoalPosY()))
			== (environment->getCellAt(pos_x, pos_y))) {
		return (true);
	}
	return (false);
}

bool AlgoAStar::step() {
	return (true);
}

void AlgoAStar::print_board() {
	environment->print_board();
}

void AlgoAStar::print_board_debug() {
	environment->print_board_debug();
}

void AlgoAStar::print_path() {
	for (auto &elem : path) {
		std::cout << "(" << elem->getPosX() << "," << elem->getPosY() << ")"
				<< std::endl;
	}
}

double AlgoAStar::calculateHValue(int pos_x, int pos_y) {
	return ((long) std::sqrt(
			((pos_x - environment->getGoalPosX())
					* (pos_x - environment->getGoalPosX()))
					+ ((pos_y - environment->getGoalPosY())
							* (pos_y - environment->getGoalPosY()))) * 10);

}

bool AlgoAStar::run() {
	Cell *curent_cell = nullptr;
	init();
	while (open_list.empty() != true) {
		curent_cell = removeLowGCostCell();

		if (curent_cell->getCellType() == CellType::GOAL) {
			break;
		}

		curent_cell->setCellStatus(CellStatus::EXPLORED);

		close_list.insert(curent_cell);

		for (uint i = 0; i < directions.size(); ++i) {

			if (isValid(directions[i].first + curent_cell->getPosX(),directions[i].second + curent_cell->getPosY()) == false) {
				continue;
			} // is not a valid position
			Cell *next_cell = &(environment->getCellAt(
					directions[i].first + curent_cell->getPosX(),
					directions[i].second + curent_cell->getPosY()));
			// is obstacle or already visited
			if (next_cell->getCellType() == CellType::OBSTACLE
					|| close_list.find(next_cell) != close_list.end()) {
				continue;
			}
			next_cell->setCellStatus(CellStatus::CALCULATED);
			double totalCost = curent_cell->getGCost() + ((i < 4) ? 10 : 14); // diagonal sqrt(2) * 10 to get int values

			std::list<Cell*>::iterator findIter = std::find(open_list.begin(),
					open_list.end(), next_cell);
			if (findIter == open_list.end()) {   // not found
				next_cell->setGCost(totalCost);
				next_cell->setHCost(
						calculateHValue(
								directions[i].first + curent_cell->getPosX(),
								directions[i].second + curent_cell->getPosY()));
				next_cell->setFCost(next_cell->getGCost() + next_cell->getHCost());
				next_cell->setPred(curent_cell);
				open_list.push_back(next_cell);
			} else if (totalCost < next_cell->getGCost()) {
				next_cell->setPred(curent_cell);
				next_cell->setGCost(totalCost);
			}
			notify();
			//usleep(10);
		}
	}

	notify();
	while (curent_cell != curent_cell->getPred()) {
		curent_cell->setCellStatus(CellStatus::PATH);
		path.push_back(curent_cell);
		curent_cell = curent_cell->getPred();
	}

	close_list.clear();
	open_list.clear();
	notify();
	return (true);
}

} /* namespace mpal */

