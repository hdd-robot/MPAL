/*
 * AlgoNav.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ALGONAV_H_
#define ALGONAV_H_

#include "Observable.h"
#include "Environment.h"
#include "Graph.h"
#include "Data.h"

namespace mpal {

enum class AlgoType {
	NOT_SET, RRT_STAR, DSTARLITE, DSTARCLASSIC, ASTAR, D_PATH
};

class AlgoNav: public Observable<Data> {
protected:
	AlgoType algoName = AlgoType::NOT_SET;
	Environment *environment;
	Graph graph;

	std::vector<std::pair<int, int>> lst_vetrices;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lst_adges;

	int env_width, env_height;
	int robot_pos_x, robot_pos_y;
	int start_pos_x, start_pos_y;
	int goal_pos_x, goal_pos_y;

public:
	AlgoNav();
	AlgoNav(Environment*);
	virtual ~AlgoNav();

	virtual bool init()=0;
	virtual bool step()=0;
	virtual bool run()=0;

	virtual Event<Data>* getEvent() {
		Data *d = new Data;
		d->algo_type = algoName;
		d->env = environment;
		d->lst_vertex = &lst_vetrices;
		d->lst_adge = &lst_adges;
		return new Event<Data>(d);
	}

	virtual std::vector<std::pair<int, int>> get_vertrices() {
		lst_vetrices = graph.get_list_vertex();
		return lst_vetrices;
	}

	virtual std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> get_adges() {
		lst_adges = graph.get_list_adge();
		return lst_adges;
	}


};

} /* namespace mpal */

#endif /* ALGONAV_H_ */
