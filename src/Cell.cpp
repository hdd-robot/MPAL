/*
 * Cell.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: ros
 */

#include "Cell.h"
#include <iostream>

namespace mpal {

Cell::Cell() {

}

Cell::~Cell() {

}

std::ostream& operator <<(std::ostream &param, const Cell &cell) {
	return param << "x";
}

} /* namespace mpal */
