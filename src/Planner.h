/*
 * Planner.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef PLANNER_H_
#define PLANNER_H_

#include "Environment.h"
#include "EnvironmentContinue.h"
#include "EnvironmentCell.h"
#include "AlgoNav.h"
#include "AlgoCellBased.h"
#include "AlgoAStar.h"
#include "AlgoRRTStar.h"
#include "EnvDrawArea.h"
#include "AlgoDPath.h"

namespace mpal {

class EnvDrawArea;

class Planner {
private:
	AlgoType algotype = AlgoType::NOT_SET;
	Environment *env;
	std::vector<std::pair<int, int>> lst_vertex;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lst_adge;
	EnvDrawArea *envArea = nullptr;
	GraphDrawArea *graphArea = nullptr;
public:

	Planner(Environment*);
	Planner(Environment*, Gtk::DrawingArea*);
	Planner(Environment*, Gtk::DrawingArea*, Gtk::DrawingArea*);

	virtual ~Planner();

	void run();

	void run_aStar();

	void run_rrtStar();

	void run_dStarLite();

	void run_dPath();

	bool valid_param();

	void setAlgotype(AlgoType at) {
		algotype = at;
	}

};

} /* namespace mpal */

#endif /* PLANNER_H_ */
