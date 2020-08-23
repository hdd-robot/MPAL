/*
 * Environnement.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Obstacle.h"
#include "Point.h"
#include "Line.h"

namespace mpal {

class Environment {
protected:
	int width, height;
	int robot_pos_x = -1, robot_pos_y = -1;
	int start_pos_x = -1, start_pos_y = -1;
	int goal_pos_x = -1, goal_pos_y = -1;
	std::vector<Obstacle*> lst_obstacles;

public:
	Environment(int, int);
	virtual ~Environment();
	virtual void draw_outline();
	virtual bool add_obstacle(Obstacle*);
	virtual bool set_robot_pos(int, int);
	virtual bool set_start_pos(int, int);
	virtual bool set_goal_pos(int, int);
	virtual void print_board()=0;

	int getGoalPosX() const {
		return goal_pos_x;
	}

	void setGoalPosX(int x) {
		goal_pos_x = x;
	}

	int getGoalPosY() const {
		return goal_pos_y;
	}

	void setGoalPosY(int y) {
		goal_pos_y = y;
	}

	int getHeight() const {
		return height;
	}

	const std::vector<Obstacle*>& getLstObstacles() const {
		return lst_obstacles;
	}

	int getRobotPosX() const {
		return robot_pos_x;
	}

	void setRobotPosX(int x) {
		robot_pos_x = x;
	}

	int getRobotPosY() const {
		return robot_pos_y;
	}

	void setRobotPosY(int y) {
		robot_pos_y = y;
	}

	int getStartPosX() const {
		return start_pos_x;
	}

	void setStartPosX(int x) {
		start_pos_x = x;
	}

	int getStartPosY() const {
		return start_pos_y;
	}

	void setStartPosY(int y) {
		start_pos_y = y;
	}

	int getWidth() const {
		return width;
	}
};

} /* namespace mpal */

#endif /* mpal */
