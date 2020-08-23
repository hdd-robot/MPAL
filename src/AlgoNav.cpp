/*
 * AlgoNav.cpp
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "AlgoNav.h"

namespace mpal {

AlgoNav::AlgoNav() {
}

AlgoNav::AlgoNav(Environment *env) :
		environment(env) {

}

AlgoNav::~AlgoNav() {
//	delete environment;
//	delete graph;
}

} /* namespace mpal */
