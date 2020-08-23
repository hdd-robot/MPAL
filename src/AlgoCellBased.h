/*
 * AlgoCellBased.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef UML_ALGOCELLBASED_H_
#define UML_ALGOCELLBASED_H_
#include <queue>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include "AlgoNav.h"
#include "EnvironmentCell.h"
namespace mpal {

class AlgoCellBased: public AlgoNav {
protected:
	EnvironmentCell *environment; //override

public:
	AlgoCellBased(EnvironmentCell*);
	virtual ~AlgoCellBased();

};

} /* namespace mpal */

#endif /* UML_ALGOCELLBASED_H_ */
