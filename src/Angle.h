/*
 * Angle.h
 *
 *  Created on: 3 juin 2020
 *      Author: hdd
 */

#ifndef ANGLE_H_
#define ANGLE_H_
#include <iostream>
#include <vector>
namespace mpal {

class Angle{
public:

	Angle(){}

	Angle(int id_p, double teta_min_p, double teta_max_p,double teta_dist_min_p, double teta_dist_max_p, double teta_diff_p) :
			id(id_p), teta_min(teta_min_p), teta_max(teta_max_p), teta_dist_min(teta_dist_min_p),
			teta_dist_max(teta_dist_max_p), teta_diff(teta_diff_p) {}

	virtual ~Angle(){}

	void print(){
		std::cout << " Ang : "           << id
				  << " teta_min : "      << teta_min
				  << " teta_max : "      << teta_max
				  << " teta_dist_min : " << teta_dist_min
				  << " teta_dist_max : " << teta_dist_max
				  << " teta_diff : "     << teta_diff
				  << std::endl;
	}

	bool operator < (Angle& ang){
		return (teta_min < ang.teta_min);
	}

	int id;
	double teta_min;
	double teta_max;
	double teta_dist_min;
	double teta_dist_max;
	double teta_diff;

	std::vector<std::pair<int,int>> waypoints;
};

} /* namespace mpal */

#endif /* ANGLE_H_ */
