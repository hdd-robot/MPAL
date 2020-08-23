/*
 * AlgoRRTStar.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ALGORRTSTAR_H_
#define ALGORRTSTAR_H_

#include <utility>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <complex>
#include "AlgoContEnvBased.h"
#include "Data.h"
#include "Observable.h"

namespace mpal {

class AlgoRRT: public AlgoContEnvBased {
protected:

	std::pair<int, int> get_random_point();
	std::pair<int, int> get_next_pos(int, int, int);
	bool goal_is_reached(int, int);

	uint distance = 50;

public:
	AlgoRRT(EnvironmentContinue*);
	virtual ~AlgoRRT();
	virtual bool init();
	virtual bool step();
	virtual bool run();
	virtual void set_distance(int);
	double eclud_dist(int, int, int, int);

	virtual Event<Data>* getEvent() {
		Data *d = new Data;
		d->algo_type = algoName;
		d->env = environment;
		d->lst_vertex = &lst_vetrices;
		d->lst_adge = &lst_adges;
		return new Event<Data>(d);
	}

};

} /* namespace mpal */

#endif /* ALGORRTSTAR_H_ */
