/*
 * Lidar.h
 *
 *  Created on: 26 mai 2020
 *      Author: hdd
 */

#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_
#include <vector>
#include <cmath>
#include <complex>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Environment.h"
#include "EnvironmentCell.h"
#include "EnvironmentContinue.h"

namespace mpal {

class Lidar {
protected:
	int radus  = 50 ;
	int sample = 360;
	int posx;
	int posy;
	Environment* env;
	std::vector<double> lst_scan;

	boost::numeric::ublas::matrix<int> scan_grid;
	std::vector<std::pair<int,int>> lst_points;


	std::vector<double>  scan_cont_env(EnvironmentContinue*);
	std::vector<double>  scan_cell_env(EnvironmentCell*);
	bool  obstacle_in_scan_area(Obstacle*);
	bool  pointCircle(Point&, Cercle&);
	float dist(Point&, Point&);
	bool  linePoint(Line&, Point&);
	bool  lineCircle(Line&, Cercle&);
	bool  circleCircle(Cercle, Cercle);
	void  set_int_grid(int,int, int); // 0,0 is in center
	int   get_int_grid(int, int); // 0,0 is in center
	void  set_obstacle_grid(int, int, int); // if value == -1 not set



public:
	Lidar(Environment*, int, int, int);

	std::vector< double> scan();
	std::vector< double> move(int,int);

	void clear();

	void print_grid();

	virtual ~Lidar();

	int getPosx() const {
		return (posx);
	}

	int getPosy() const {
		return (posy);
	}

	int getRadus() const {
		return (radus);
	}

	void setRadus(int radus = 50) {
		this->radus = radus;
	}

	int getSample() const {
		return (sample);
	}

	void setSample(int sample = 360) {
		this->sample = sample;
	}

	std::vector<std::pair<int, int>>& getLstPoints() {
		return (lst_points);
	}
};

} /* namespace mpal */

#endif /* SRC_LIDAR_H_ */
