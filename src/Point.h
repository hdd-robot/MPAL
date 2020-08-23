/*
 * Point.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef POINT_H_
#define POINT_H_

#include <vector>

#include "Obstacle.h"

namespace mpal {

class Point: public Obstacle {

private:
	int pos_x;
	int pos_y;

public:
	Point(int, int);
	Point(const Point&) = default;
	virtual ~Point();
	virtual void set_pos(int, int);
	virtual void move(int, int);
	virtual std::vector<std::pair<int, int>> draw();
	virtual std::vector<std::pair<int, int>> draw_outline(){
		return (draw());
	}

	Point* cloner() const {
		return (new Point(*this));
	}
	int getPosX() const {
		return (pos_x);
	}

	int getPosY() const {
		return (pos_y);
	}

	;

};

} /* namespace mpal */

#endif /* POINT_H_ */

