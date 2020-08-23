/*
 * Cercle.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef CERCLE_H_
#define CERCLE_H_
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <stack>
#include <utility>
#include "Obstacle.h"
#include "Point.h"

namespace mpal {

class Cercle: public Obstacle {
private:
	Point center;
	int unsigned radus;

	int get_pos_grid(boost::numeric::ublas::matrix<int>& grid, int px, int py);
	void set_pos_grid(boost::numeric::ublas::matrix<int>& grid, int px, int py, int val);

	virtual std::vector<std::pair<int, int>> draw_cercle();

public:
	Cercle(Point, unsigned int);
	Cercle(const Cercle&) = default;
	virtual ~Cercle();
	virtual void set_pos(int, int);
	virtual void move(int, int);
	virtual std::vector<std::pair<int, int>> draw();

	virtual std::vector<std::pair<int, int>> draw_outline(){
		return (draw_cercle());
	}

	Cercle* cloner() const {
		return new Cercle(*this);
	}

	Point& getCenter() {
		return center;
	}

	unsigned int getRadus() {
		return radus;
	}

	;
};

} /* namespace mpal */

#endif /* CERCLE_H_ */
