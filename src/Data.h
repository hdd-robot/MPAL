/*
 * data.h
 *
 *  Created on: 18 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef DATA_H_
#define DATA_H_

#include "Environment.h"
#include "Lidar.h"
#include "Angle.h"
#include "Graph.h"

namespace mpal {
enum class AlgoType
;

class Data {
public:
	AlgoType algo_type;
	Environment *env;
	Graph* graph = nullptr;
	Lidar* lidar = nullptr;
	std::vector<std::pair<int, int>> *lst_vertex;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> *lst_adge;
	std::vector<Angle>* lst_angles_paths;
	std::vector<std::pair<int,int>>* list_waypoints;
	std::vector<Line>* lst_scan_lines;

};

} /* namespace mpal */

#endif /* DATA_H_ */
