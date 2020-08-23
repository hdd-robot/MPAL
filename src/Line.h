/*
 * Line.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef LINE_H_
#define LINE_H_
#include <cmath>
#include "Obstacle.h"
#include "Point.h"

namespace mpal {

class Line: public Obstacle {
private:
	Point point_start;
	Point point_end;
public:
	Line(Point, Point);
	Line(const Line&) = default;
	virtual ~Line();
	virtual void set_pos(int, int);
	virtual void move(int, int);
	virtual std::vector<std::pair<int, int>> draw();
	virtual std::vector<std::pair<int, int>> draw_outline(){
			return (draw());
	}

	Line* cloner() const {
		return new Line(*this);
	}

	Point& getPointEnd() {
		return point_end;
	}

	Point& getPointStart() {
		return point_start;
	}

	double get_dist();

};

} /* namespace mpal */

#endif /* LINE_H_ */
