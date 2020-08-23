/*
 * Lidar.cpp
 *
 *  Created on: 26 mai 2020
 *      Author: hdd
 */

#include "Lidar.h"

namespace mpal {

/**
 * \fn Lidar constructor
 * \param Environment, position of LIDAR and radius of laser scan
 */
Lidar::Lidar(Environment* environement, int px, int py, int rad):env(environement), posx(px), posy(py), radus(rad) {
	// We add one to get odd number
	scan_grid.resize(rad*2 + 1 , rad*2 + 1 );

}

/**
 * Destructor
 */
Lidar::~Lidar() {

}


void Lidar::clear() {
	lst_scan.clear();

	for (int i = 0; i < scan_grid.size1(); i++) {
		for (int j = 0; j < scan_grid.size2(); j++) {
			scan_grid(i, j) = -1;
		}
	}

	Cercle tmpC(Point(0, 0), radus);
	std::vector<std::pair<int, int>> val_draw = tmpC.draw();

	for (auto elem : val_draw) {
		set_int_grid(elem.first, elem.second, 0);
	}

	//put center pos
	set_int_grid(0, 0, 2);

}



/**
 * \brief if value is -1 then not set value
 * @param px
 * @param py
 * @param val
 */
void Lidar::set_obstacle_grid(int px, int py, int val) {
	int new_px = floor(radus + 1) + px;
	int new_py = floor(radus + 1) + py;

	if ((new_px <0 ) || (new_py < 0) || (new_px >=  2 * radus + 1) || (new_py >= 2 * radus + 1)) {
		return;
	}
	if(scan_grid(new_px,new_py) == -1 ){
		return;
	}
	scan_grid(new_px,new_py) = val;
}



/**
 * \prief put cal at [i,j] of matrix
 */
void Lidar::set_int_grid(int px, int py, int val) {
	int new_px = floor(radus + 1) + px;
	int new_py = floor(radus + 1) + py;

	if ((new_px <0 ) || (new_py < 0) || (new_px >=  2 * radus + 1) || (new_py >= 2 * radus + 1)) {
		return;
	}
	scan_grid(new_py,new_px) = val;
}


/**
 * \brief get value
 */
int Lidar::get_int_grid(int px, int py) {
	int new_px = floor(radus + 1) + px;
	int new_py = floor(radus + 1) + py;
	return (scan_grid(new_py,new_px));
}




std::vector<double> Lidar::move(int px, int py) {
	posx = px;
	posy = py;
	return (scan());
}


std::vector<double> Lidar::scan() {
	//init values
	clear();

	EnvironmentContinue* env_cont = dynamic_cast<EnvironmentContinue*>(env);
	if(env_cont != nullptr){
		return (scan_cont_env(env_cont));

	}

	EnvironmentCell* env_cell = dynamic_cast<EnvironmentCell*>(env);
	if(env_cell != nullptr){
		return (scan_cell_env(env_cell));
	}

	return (lst_scan);
}

/**
 * \brief scan_cont_env
 */
std::vector<double> Lidar::scan_cont_env(EnvironmentContinue* envCont){
	const std::vector<Obstacle*>& lst_obstacles = envCont->getLstObstacles();
	for(auto obs : lst_obstacles){
		// We deal only with obstacles within detector range
		if(obstacle_in_scan_area(obs) == true ){
			std::vector<std::pair<int, int>>drw = obs->draw();
			for(auto elem : drw){
				int npx =  (-posx) + elem.first;
				int npy =  (-posy) + elem.second;
				set_obstacle_grid(npx,npy,1);
			}
		}
	}

	lst_points.clear();
	lst_scan.clear();
	//Cercle laser(Point(posx,posy),radus);
	//std::vector<std::pair<int, int>> outline = laser.draw_outline();


	double step = (M_PI * 2) / sample;
	double ang = 0;
	while (ang < (M_PI * 2)){
		std::complex<double> vec(std::polar(static_cast<double>(radus), ang));
		int vec_x = static_cast<int>(real(vec));
		int vec_y = static_cast<int>(imag(vec));

		int tpx  = posx + vec_x ;
		int tpy  = posy - vec_y;


		Line tmp_line(Point(posx,posy), Point(tpx,tpy));
		std::vector<std::pair<int, int>> lst_line_points = tmp_line.draw();

		int npx = (-posx) +tpx;
		int npy = (-posy) +tpy;

		std::pair<int,int> start(0 ,0);
		std::pair<int,int> end = std::make_pair(npx,npy);

		for(auto elem_line : lst_line_points){
			npx =  (-posx) + elem_line.first;
			npy =  (-posy) + elem_line.second;

			if(scan_grid(npx+(radus),npy+(radus))==1){
				break;
			}
			end = std::make_pair(npx,npy);

			//std::cout << npx << "," << npy << std::endl;
			//std::cout << npx+(radus) << "," << npy+(radus) << std::endl;
		}

		lst_points.push_back(end);

		Line tmp_ln(Point(start.first,start.second), Point(end.first,end.second));
		double val = tmp_ln.get_dist();

		if(val >= radus-5){
			val = std::numeric_limits<double>::infinity();
		}
		lst_scan.push_back(val);
		ang = ang + step;
	}
	return (lst_scan);
}



std::vector<double> Lidar::scan_cell_env(EnvironmentCell* envCell){
	return (lst_scan);
}

/**
 * \brief Used to find out if the obstacle is in the scan field
 */
bool Lidar::obstacle_in_scan_area(Obstacle* obs) {
	Cercle lidarCircle(Point(posx,posy),radus);
	Line* line = dynamic_cast<Line*>(obs);
	if(line != nullptr){
		return (lineCircle(*line,lidarCircle));
	}


	Cercle* cercle = dynamic_cast<Cercle*>(obs);
	if(cercle != nullptr){
		return (circleCircle(*cercle,lidarCircle));
	}

	// todo : add polygon and other forms (Polygones)

	return (false);
}


/**
 * \brief Used to check whether a point is contained in a circle
 * \param point, circle
 * \return true if point is in circle false otherwise
 */
bool Lidar::pointCircle(Point& p, Cercle& c) {
  int distX = p.getPosX() - c.getCenter().getPosX() ;
  int distY = p.getPosY() - c.getCenter().getPosY();
  float distance = sqrt( (distX*distX) + (distY*distY) );
  if (distance <= c.getRadus()) {
    return (true);
  }
  return (false);
}


/**
 * \brief get distance between p1 and p2
 */
float Lidar::dist(Point& p1, Point& p2){
	int distX = p1.getPosX() - p2.getPosX();
	int distY = p1.getPosY() - p2.getPosY();
	float distance = sqrt( (distX*distX) + (distY*distY) );
	return (distance);
}


/**
 * \brief return true if collision between line and point
 */
bool Lidar::linePoint(Line& l, Point& p) {
  float d1 = dist(p, l.getPointStart());
  float d2 = dist(p, l.getPointEnd());
  float lineLen = dist(l.getPointStart(),l.getPointEnd());

  // since floats are so minutely accurate, add
  // a little buffer zone that will give collision
  float buffer = 0.1;    // higher # = less accurate

  // if the two distances are equal to the line's
  // length, the point is on the line!
  // note we use the buffer here to give a range,
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return (true);
  }
  return (false);
}


/**
 * \brief return true if collision between line and circle
 */
bool Lidar::lineCircle(Line& l, Cercle& c){

  // is either end INSIDE the circle?
  // if so, return true immediately
  bool inside1 = pointCircle(l.getPointStart(),c);
  bool inside2 = pointCircle(l.getPointEnd(),c);
  if (inside1 || inside2) {
	  return (true);
  }

  // get length of the line
  float len = dist(l.getPointStart(),l.getPointEnd());

  // get dot product of the line and circle
  float dot = ( ((c.getCenter().getPosX()-l.getPointStart().getPosX())*(l.getPointEnd().getPosX()-l.getPointStart().getPosX())) +
		  ((c.getCenter().getPosY()-l.getPointStart().getPosY())*(l.getPointEnd().getPosY()-l.getPointStart().getPosY())) ) / pow(len,2);

  // find the closest point on the line
  float closestX = l.getPointStart().getPosX() + (dot * (l.getPointEnd().getPosX()-l.getPointStart().getPosX()));
  float closestY = l.getPointStart().getPosY() + (dot * (l.getPointEnd().getPosY()-l.getPointStart().getPosY()));

  // is this point actually on the line segment?
  // if so keep going, but if not, return false
  Point pClose(closestX,closestY);
  bool onSegment = linePoint(l,pClose);
  if (!onSegment) {
	  return (false);
  };

  float distance = dist(pClose,c.getCenter());

  if (distance <= c.getRadus()) {
	return (true);
  }

  return (false);
}


/**
 * \brief return true if collision circle
 * \return return true if collision false otherwise
 */
bool Lidar::circleCircle(Cercle c1, Cercle c2) {
  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  int distX = c1.getCenter().getPosX() - c2.getCenter().getPosX();
  int distY = c1.getCenter().getPosY() - c2.getCenter().getPosY();
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  if (distance <= c1.getRadus()+c2.getRadus()) {
    return (true);
  }
  return (false);
}


/**
 * \brief print to dugo todo : delte this function
 */
void Lidar::print_grid() {
	for (int j = 0; j < scan_grid.size1(); j++) {
		for (int i = 0; i < scan_grid.size2(); i++) {
			int val = scan_grid(i,j) ;
			if(val ==  2)  {std::cout << 'X';}
			if(val ==  1)  {std::cout << '*';}
			if(val ==  0)  {std::cout << '.';}
			if(val == -1) {std::cout <<  '_';}
		}
		std::cout << std::endl;
	}
}



} /* namespace mpal */












