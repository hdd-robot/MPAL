/*
 * AlgoDPath.cpp
 *
 *  Created on: 20 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "AlgoDPath.h"

namespace mpal {

AlgoDPath::AlgoDPath(EnvironmentContinue *env) :
		AlgoContEnvBased(env) {
		algoName = AlgoType::D_PATH;
}


AlgoDPath::~AlgoDPath() {
	if(lidar_ptr != nullptr){
		delete lidar_ptr;
	}
}

bool AlgoDPath::init() {
	return (true);
}

bool AlgoDPath::step() {
	return (true);
}

void AlgoDPath::add_scan_lines() {
	if(lidar_ptr == nullptr){
		return;
	}

	lst_scan_lines.clear();

	for(auto elem : lidar_ptr->getLstPoints()){
		int p1_x = lidar_ptr->getPosx();
		int p1_y = lidar_ptr->getPosy();
		int p2_x = lidar_ptr->getPosx() + elem.first ;
		int p2_y = lidar_ptr->getPosy() + elem.second;
		lst_scan_lines.push_back(Line(Point(p1_x,p1_y),Point(p2_x,p2_y)));
	}
}

bool AlgoDPath::run() {
	std::cout << " run D PATH " << std::endl;

	environment->set_robot_pos(environment->getStartPosX(),environment->getStartPosY());
	int r_posx = environment->getRobotPosX();
	int r_posy = environment->getRobotPosY();

	radius_laser_scan = 150;
	sample_laser_scan = 180;

	// create lidar
	lidar_ptr = new Lidar(environment,r_posx,r_posy,radius_laser_scan);
	lidar_ptr->setSample(sample_laser_scan);

	double dx = abs(environment->getRobotPosX() - environment->getGoalPosY());
	double dy = abs(environment->getRobotPosX() - environment->getGoalPosY());

	graph.add_start_vtx(std::make_pair(environment->getStartPosX(),environment->getStartPosY()));
	graph.add_goal_vtx(std::make_pair(environment->getGoalPosX(),environment->getGoalPosY()));

	while(!(graph.goal_is_reached())){
		std::cout << " -- while D_PATH"<< std::endl ;

		r_posx = environment->getRobotPosX();
		r_posy = environment->getRobotPosY();
		lidar_ptr->move(r_posx,r_posy);
		std::vector<double> datascan = lidar_ptr->scan();

		std::vector<Angle>lst_angl = get_angles_obj(datascan);
		std::vector<Angle>lst_path = get_angles_path(lst_angl);
		std::vector<std::pair<int,int>>lst_way_point = add_waypoints(lst_path,r_posx,r_posy);

		add_scan_lines();
		notify();

		for(auto elem: lst_way_point){
			graph.add_waypoint_vertex(elem);
		}

		int id_next = graph.get_next_vertex();
		graph.set_robot_pos(id_next);
		environment->set_robot_pos(graph.get_pos_x(id_next),graph.get_pos_y(id_next));



		graph.trace_graph();


		// get lines to display


		sleep(3);
	}

	notify();
	std::cout << "END DPATH" << std::endl ;

//	std::cout << "lst_way_point" << std::endl ;
//	for(auto elem : lst_way_point){
//		std::cout << elem.first << "," << elem.second << std::endl ;
//	}
//	std::cout << "end__lst_way_point" << std::endl ;


//	std::cout << "lst_scan_lines" << std::endl ;
//	for(auto elem : lst_scan_lines){
//		std::cout << "("<<elem.getPointStart().getPosX() << "," << elem.getPointStart().getPosY() << "),("<< elem.getPointEnd().getPosX() << "," << elem.getPointEnd().getPosY()<<")" << std::endl ;
//	}
//	std::cout << "end__lst_scan_lines" << std::endl ;



	std::cout << std::endl ;
	sleep(1000);
	return (true);
}

/**
 * \brief get list of Angles Objects
 * @param lst_laser_scan
 * @return list of Angles
 */
std::vector<Angle> AlgoDPath::get_angles_obj(std::vector<double> lst_laser_scan) {

	std::vector<Angle> list_angles;
	//Interval pour dire que deux objet sont présents
	double max_interval =25.0;


	std::vector<double>::iterator it_m = std::min_element(lst_laser_scan.begin(),lst_laser_scan.end());

	//Si aucun chemin à améliorer : escargo , labyrith
	if(*(std::max_element(lst_laser_scan.begin(),lst_laser_scan.end())) != std::numeric_limits<double>::infinity()){
		return (list_angles);
	}

	// Si y a pas d'obstacles alors on retour un seul élément
	if(*it_m == std::numeric_limits<double>::infinity()){
		list_angles.push_back(Angle(1,0,2*M_PI, radius_laser_scan,radius_laser_scan,2*M_PI));
		return (list_angles);
	}

	int it_min = it_m - lst_laser_scan.begin();
	int it_beg = 0 ;
	int it_end = sample_laser_scan - 1 ;
	int count = 0 ;
	while (lst_laser_scan[it_min] != std::numeric_limits<double>::infinity()){
		int it_l = it_min-1;
		int it_r = it_min+1;
		while (true){

			if (it_l < it_beg){
				break;
			}
			if (abs(lst_laser_scan[it_l] - lst_laser_scan[it_l + 1]) >= max_interval){
				break;
			}
			it_l = it_l - 1;

		}
		while (true){

			if (it_r > it_end){
				break;
			}
			if (abs(lst_laser_scan[it_r] - lst_laser_scan[it_r - 1]) >= max_interval){
				break;
			}
			it_r = it_r + 1;

		}
		count += 1;

		// todo : min <--> max inversés
		Angle a(count,
				((it_l + 1) * 2 * M_PI) / float(sample_laser_scan),
				((it_r - 1) * 2 * M_PI) / float(sample_laser_scan),
				lst_laser_scan[it_l + 1],
				lst_laser_scan[it_r - 1],



				0);
		list_angles.push_back(a);
		while (it_l != it_r){
			lst_laser_scan[it_l] = std::numeric_limits<double>::infinity();
			it_l += 1;
		}
		it_min = std::min_element(lst_laser_scan.begin(),lst_laser_scan.end()) - lst_laser_scan.begin();
	}

	return (list_angles);
}

std::vector<Angle> AlgoDPath::get_angles_path(std::vector<Angle> lst_angles_obj) {
	lst_angles_paths.clear();

	if(lst_angles_obj.size()==0) {
		return (lst_angles_paths);
	}

	std::sort(lst_angles_obj.begin(),lst_angles_obj.end());

	std::vector<Angle>::iterator fst = lst_angles_obj.begin();
	std::vector<Angle>::iterator lst = lst_angles_obj.end();

	if (fst->id != std::next(lst, -1)->id){
		if (fst->teta_min < (2 * M_PI / sample_laser_scan) and (lst->teta_max > ((2 * M_PI / sample_laser_scan) - (2 * M_PI)))){
			lst->teta_max = fst->teta_max;
			lst->teta_dist_max = fst->teta_dist_max;
			fst = lst_angles_obj.erase(lst_angles_obj.begin());
		}
	}
	else{
		Angle a;
		a.id = 1;

		if (lst_angles_obj[0].teta_min < 0.1 and lst_angles_obj[0].teta_max > 6.0){
			a.teta_max = lst_angles_obj[0].teta_max;
			a.teta_min = lst_angles_obj[0].teta_min;
			a.teta_dist_max = lst_angles_obj[0].teta_dist_max;
			a.teta_dist_min = lst_angles_obj[0].teta_dist_min;
		}
		else {
			a.teta_max = lst_angles_obj[0].teta_min;
			a.teta_min = lst_angles_obj[0].teta_max;
			a.teta_dist_max = lst_angles_obj[0].teta_dist_min;
			a.teta_dist_min = lst_angles_obj[0].teta_dist_max;
		}

		lst_angles_paths.push_back(a);
		return (lst_angles_paths);
	}

	int it_beg = 0;
	int it_end = lst_angles_obj.size() ;//- 1;
	int it_lst = it_beg;
	int count = 0;
	while (it_lst <= it_end){
		Angle a;
		count = count + 1;
		a.id = count;
		a.teta_min = lst_angles_obj[it_lst].teta_max;
		a.teta_dist_min = lst_angles_obj[it_lst].teta_dist_max;
		if (it_lst == it_end){
			a.teta_max = lst_angles_obj[it_beg].teta_min;
			a.teta_dist_max = lst_angles_obj[it_beg].teta_dist_min;
		}
		else{
			a.teta_max = lst_angles_obj[it_lst + 1].teta_min;
			a.teta_dist_max = lst_angles_obj[it_lst + 1].teta_dist_min;
		}
		lst_angles_paths.push_back(Angle(a.id, a.teta_min, a.teta_max, a.teta_dist_min, a.teta_dist_max, 0));
		it_lst += 1;
	}
	return (lst_angles_paths);
}

std::vector<std::pair<int,int>> AlgoDPath::add_waypoints(std::vector<Angle>& lst_path, int posx, int posy) {

	list_waypoints.clear();

	double diff_teta;
	int nbr_waypoints;

	for (Angle& ang  : lst_path){
		double tmin = ang.teta_min;
		double tmax = ang.teta_max;
		if (ang.teta_min > ang.teta_max){
			diff_teta = (2 * M_PI) - abs(ang.teta_max - ang.teta_min);
		}
		else{
			diff_teta = abs(tmax - tmin);
		}
		ang.teta_diff = diff_teta;
		nbr_waypoints = int(diff_teta / waypoint_interval);
		if (nbr_waypoints == 0) {
			nbr_waypoints = 1;
		}

		double point_f = tmin;
		double step = (diff_teta) / (nbr_waypoints);
		point_f = point_f + (step / 2);

		for(int i=0 ; i< nbr_waypoints ; i++){

			double p_rad = radius_laser_scan;

			if((ang.teta_dist_min < radius_laser_scan - 5) || (ang.teta_dist_max < radius_laser_scan - 5)){
				p_rad = ang.teta_dist_min + (ang.teta_dist_max - ang.teta_dist_min)/2;
			}

			std::complex<double> pointway(std::polar(static_cast<double>(p_rad), point_f));
			//pointway = pointway + std::complex<double>(posx,-posy);

			int px = posx + pointway.real();
			int py = posy - pointway.imag();

			ang.waypoints.push_back(std::make_pair(px, py));
			list_waypoints.push_back(std::make_pair(px, py));

			point_f = point_f + (step);
		}
	}
	return(list_waypoints);
}



} /* namespace mpal */




























