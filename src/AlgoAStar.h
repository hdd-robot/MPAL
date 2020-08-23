/*
 * AlgoAStar.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ALGOASTAR_H_
#define ALGOASTAR_H_
#include <cmath>
#include "AlgoCellBased.h"


namespace mpal {

class AlgoAStar;

class AlgoAStar: public AlgoCellBased {
private:

	std::list<Cell*> open_list;
	std::set<Cell*> close_list;
	std::vector<Cell*> path;

	std::vector<std::pair<int, int>> directions;

	Cell* removeLowGCostCell() {
		if (open_list.empty() == true) {
			return nullptr;
		}
		std::list<Cell*>::iterator it, it_tmp;
		it_tmp = open_list.begin();
		Cell *min_cell = *(it_tmp);
		for (it = open_list.begin(); it != open_list.end(); it++) {
			if (min_cell->getHCost() + min_cell->getGCost()
					> (*it)->getHCost() + (*it)->getGCost()) {
				min_cell = *it;
				it_tmp = it;
			}
		}
		open_list.erase(it_tmp);
		return min_cell;
	}

public:
	AlgoAStar(EnvironmentCell*);
	virtual ~AlgoAStar();
	virtual bool init();
	virtual bool run();
	virtual bool step();
	virtual void print_board();
	virtual void print_board_debug();
	virtual void print_path();

	bool isValid(int, int);
	bool isUnBlocked(int, int);
	bool isDestination(int, int);
	double calculateHValue(int, int);

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

#endif /* ALGOASTAR_H_ */
