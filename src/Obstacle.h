/*
 * Obstacle.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef Obstacle_H_
#define Obstacle_H_

#include <vector>

namespace mpal {

class Obstacle {

public:
	Obstacle();

	Obstacle(Obstacle&);
	Obstacle(const Obstacle&) = default;
	virtual ~Obstacle();

	virtual void set_pos(int, int) = 0;
	virtual void move(int, int) = 0;

	virtual std::vector<std::pair<int, int>> draw()=0;
	virtual std::vector<std::pair<int, int>> draw_outline()=0;




	virtual Obstacle* cloner() const = 0;


};

} /* namespace mpal */

#endif /* Obstacle_H_ */
