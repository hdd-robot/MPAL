/*
 * Environnement.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "EnvironmentContinue.h"

namespace mpal {

EnvironmentContinue::EnvironmentContinue(int pWidth, int pHeight) :
		Environment(pWidth, pHeight) {

}

EnvironmentContinue::~EnvironmentContinue() {

}

std::ostream& operator <<(std::ostream &param, const EnvironmentContinue &env) {
	return (param);
}

void EnvironmentContinue::print_board() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
}

} /* namespace mpal */
