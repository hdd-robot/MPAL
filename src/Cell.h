/*
 * Cell.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef CELL_H_
#define CELL_H_
#include <iostream>
#include <string>
#include <sstream>
#include "Obstacle.h"

namespace mpal {

enum class CellStatus {
	UNEXPLORED, EXPLORED, CALCULATED, PATH
};

enum class CellType {
	FREE, OBSTACLE, START, GOAL, ROBOT
};

class Cell {
private:
	unsigned int pos_x;
	unsigned int pos_y;

	CellType cellType;
	CellStatus cellStatus;

	//Used by A star
	double h_cost, g_cost, f_cost; //f(x) = g(x) + h(x)
	Cell *pred = nullptr;
	;

	//Used by D star
	Cell *succ = nullptr;
	double h, k, b;

	//Usend by D star Lite
	double g, rhs;

	Obstacle *obstacle_ptr;

public:
	Cell();
	virtual ~Cell();
	friend std::ostream& operator<<(std::ostream&, const Cell&);

	bool operator==(Cell &cell) {
		return (cell.getPosX() == pos_x && cell.getPosY() == pos_y);
	}

	void set_free() {
		obstacle_ptr = nullptr;
		cellType = CellType::FREE;
	}

	bool is_free() {
		if (getCellType() == CellType::FREE)
			return true;
		return false;
	}

	bool set_obstcale(Obstacle *obs) {
		if (!is_free())
			return false;
		obstacle_ptr = obs;
		cellType = CellType::OBSTACLE;
		return true;
	}

	bool set_start() {
		if (!is_free())
			return false;
		obstacle_ptr = nullptr;
		cellType = CellType::START;
		return true;
	}

	bool set_goal() {
		if (!is_free())
			return false;
		obstacle_ptr = nullptr;
		cellType = CellType::GOAL;
		return true;
	}

	bool set_robot() {
		if (!is_free())
			return false;
		obstacle_ptr = nullptr;
		cellType = CellType::ROBOT;
		return true;
	}

	std::string print_debug() {
		std::ostringstream str;
		str << "(" << g_cost << "," << h_cost << "," << f_cost << "," << pred
				<< ")";
		return str.str();
	}

	char printStatus() {
		switch (getCellStatus()) {
		case CellStatus::UNEXPLORED:
			return '_';
			break;
		case CellStatus::CALCULATED:
			return '%';
			break;
		case CellStatus::EXPLORED:
			return '.';
			break;
		case CellStatus::PATH:
			return '@';
			break;
		}

		return ' ';
	}

	char printType() {
		switch (getCellType()) {
		case CellType::FREE:
			return '.';
			break;
		case CellType::OBSTACLE:
			return '#';
			break;

		case CellType::START:
			return 'S';
			break;

		case CellType::GOAL:
			return 'G';
			break;

		case CellType::ROBOT:
			return '$';
			break;
		}
		return ' ';
	}

	const Obstacle* getObstaclePtr() const {
		return obstacle_ptr;
	}

	double getB() {
		return b;
	}

	void setB(double b) {
		this->b = b;
	}

	CellType getCellType() {
		return cellType;
	}

	double getFCost() {
		return f_cost;
	}

	void setFCost(double fc) {
		f_cost = fc;
	}

	double getG() {
		return g;
	}

	void setG(double g) {
		this->g = g;
	}

	double getGCost() {
		return g_cost;
	}

	void setGCost(double gc) {
		g_cost = gc;
	}

	double getH() {
		return h;
	}

	void setH(double h) {
		this->h = h;
	}

	double getHCost() {
		return h_cost;
	}

	void setHCost(double hc) {
		h_cost = hc;
	}

	unsigned int getK() {
		return k;
	}

	void setK(double k) {
		this->k = k;
	}

	void setPosX(int x) {
		this->pos_x = x;
	}

	void setPosY(int y) {
		this->pos_y = y;
	}

	unsigned int getPosX() {
		return pos_x;
	}

	unsigned int getPosY() {
		return pos_y;
	}

	double getRhs() {
		return rhs;
	}

	void setRhs(double rhs) {
		this->rhs = rhs;
	}

	Cell* getPred() {
		return pred;
	}

	void setPred(Cell *prd) {
		this->pred = prd;
	}

	Cell* getSucc() {
		return succ;
	}

	void setSucc(Cell *succ) {
		this->succ = succ;
	}

	CellStatus getCellStatus() {
		return cellStatus;
	}

	void setCellStatus(CellStatus cs) {
		this->cellStatus = cs;
	}
};

} /* namespace mpal */

#endif /* CELL_H_ */
