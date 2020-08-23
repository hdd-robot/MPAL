/*
 * AlgoContEnvBased.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ALGOCONTENVBASED_H_
#define ALGOCONTENVBASED_H_
#include "AlgoNav.h"
#include "EnvironmentContinue.h"

namespace mpal {

class AlgoContEnvBased: public AlgoNav {
protected:
	EnvironmentContinue *environment; //override
public:
	AlgoContEnvBased(EnvironmentContinue*);
	virtual ~AlgoContEnvBased();
};

} /* namespace mpal */

#endif /* ALGOCONTENVBASED_H_ */
