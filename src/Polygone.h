/*
 * Polygone.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef POLYGONE_H_
#define POLYGONE_H_

#include <vector>

#include "Obstacle.h"
#include "Point.h"

namespace mpal {

class Polygone: public Obstacle {
private:
	std::vector<Point> lst_points;
public:
	Polygone();
	virtual ~Polygone();
	virtual void set_pos(int, int);

	virtual std::vector<std::pair<int, int>> draw();

	virtual void move(int, int);
};

} /* namespace mpal */

#endif /* POLYGONE_H_ */
