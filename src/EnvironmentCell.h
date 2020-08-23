/*
 * Environnement.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ENVIRONMENTCELL_H_
#define ENVIRONMENTCELL_H_
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
#include <vector>

#include "Environment.h"
#include "Cell.h"
#include "Obstacle.h"
#include "Point.h"
#include "Cercle.h"
#include "Line.h"
#include "Polygone.h"

namespace mpal {

class EnvironmentCell: public Environment {

protected:

	boost::numeric::ublas::matrix<Cell> board;

public:
	EnvironmentCell(int, int);
	virtual ~EnvironmentCell();
	friend std::ostream& operator<<(std::ostream&, const EnvironmentCell&);

	virtual bool add_obstacle(Obstacle*);
	virtual void draw_outline();
	virtual void print_board();
	virtual void print_board_debug();
	virtual bool set_robot_pos(int, int);
	virtual bool set_start_pos(int, int);
	virtual bool set_goal_pos(int, int);
	virtual Cell& getCellAt(int, int);

	boost::numeric::ublas::matrix<Cell>& getBoard() {
		return board;
	}
};

} /* namespace mpal */

#endif /* mpal */
