/*
 * Environnement.h
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ENVIRONMENTCONTINUE_H_
#define ENVIRONMENTCONTINUE_H_
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

class Environment;

class EnvironmentContinue: public Environment {

protected:

public:
	EnvironmentContinue(int, int);
	virtual ~EnvironmentContinue();
	friend std::ostream& operator<<(std::ostream&, const EnvironmentContinue&);
	virtual void print_board();

};

} /* namespace mpal */

#endif /* mpal */
