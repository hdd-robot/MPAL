/*
 * AlgoDPath.h
 *
 *  Created on: 20 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ALGODPATH_H_
#define ALGODPATH_H_
#include <complex>
#include <vector>
#include "Data.h"
#include "Lidar.h"
#include "AlgoContEnvBased.h"
#include "Graph.h"
#include "Angle.h"

namespace mpal {

class AlgoDPath: public AlgoContEnvBased {
private:
	int radius_laser_scan = 20;
	int sample_laser_scan = 360;
	double waypoint_interval = M_PI / 6.0;

	Graph graph;

	Lidar* lidar_ptr = nullptr;

	std::vector<Angle> lst_angles_paths;
	std::vector<std::pair<int,int>> list_waypoints;
	std::vector<Line> lst_scan_lines;

	std::vector<Angle> get_angles_obj(std::vector<double> lst_laser_scan);
	std::vector<Angle> get_angles_path(std::vector<Angle>  lst_angles_obj);
	std::vector<std::pair<int,int>> add_waypoints(std::vector<Angle>& lst_path, int posx, int posy);
	void add_scan_lines();


public:

	AlgoDPath(EnvironmentContinue*);
	virtual ~AlgoDPath();
	virtual bool init();
	virtual bool step();
	virtual bool run();

	virtual Event<Data>* getEvent() {
		Data *d 			= new Data;
		d->algo_type 		= algoName;
		d->env 				= environment;
		d->lidar 			= lidar_ptr;
		d->lst_vertex 		= &lst_vetrices;
		d->lst_adge 		= &lst_adges;
		d->lst_angles_paths = &lst_angles_paths;
		d->list_waypoints 	= &list_waypoints;
		d->lst_scan_lines 	= &lst_scan_lines;
		d->graph			= &graph;
		return (new Event<Data>(d));
	}
};

} /* namespace mpal */

#endif /* ALGODPATH_H_ */
