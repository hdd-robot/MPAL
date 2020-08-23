/*
 * Cercle.cpp
 *
 *  Created on: 9 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Cercle.h"
#include <algorithm>
namespace mpal {

Cercle::Cercle(Point ctr, unsigned int rad) :
		center(ctr), radus(rad) {

}

Cercle::~Cercle() {
	// TODO Auto-generated destructor stub
}

void Cercle::set_pos(int pos_x, int pos_y) {

}

void Cercle::move(int Int, int Int1) {
}


/**
 * \brief Andres' circle
 * @return
 */
std::vector<std::pair<int, int>> Cercle::draw_cercle() {
	std::vector<std::pair<int, int>> vec;

	int x = 0;
	int y = radus;
	int d = radus - 1;

	while (y >= x) {
		vec.push_back(std::make_pair(center.getPosX() + x, center.getPosY() + y));
		vec.push_back(std::make_pair(center.getPosX() + y, center.getPosY() + x));

		vec.push_back(std::make_pair(center.getPosX() - x, center.getPosY() + y));
		vec.push_back(std::make_pair(center.getPosX() - y, center.getPosY() + x));

		vec.push_back(std::make_pair(center.getPosX() + x, center.getPosY() - y));
		vec.push_back(std::make_pair(center.getPosX() + y, center.getPosY() - x));

		vec.push_back(std::make_pair(center.getPosX() - x, center.getPosY() - y));
		vec.push_back(std::make_pair(center.getPosX() - y, center.getPosY() - x));

		if (d >= 2 * x) {
			d -= 2 * x + 1;
			x++;
		} else if (d < 2 * (radus - y)) {
			d += 2 * y - 1;
			y--;
		} else {
			d += 2 * (y - x - 1);
			y--;
			x++;
		}
	}
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	return (vec);

	return (vec);
}



/**
 * Fonction to put value in grid
 * @param grid
 * @param px
 * @param py
 * @param rad
 * @param val
 */
void Cercle::set_pos_grid(boost::numeric::ublas::matrix<int>& grid, int px, int py, int val) {

	int new_px = (radus + 1) - (center.getPosX() - px) -1 ;
	int new_py = (radus + 1) - (center.getPosY() - py) -1 ;



	if ((new_px <0 ) || (new_py < 0) || (new_px >=  2 * radus + 1) || (new_py >= 2 * radus + 1)) {
		return;
	}
	grid(new_py,new_px) = val;
}

int Cercle::get_pos_grid(boost::numeric::ublas::matrix<int>& grid, int px, int py) {
	int new_px = (radus + 1) - (center.getPosX() - px)  -1;
	int new_py = (radus + 1) - (center.getPosY() - py)  -1;


	//std::cout << "posx:" << center.getPosX() << " posy:" << center.getPosY()  << " rad:" << radus << " px:" << px <<" py:"<<py <<  " npx:" << new_px << " npx:" << new_py << std::endl;

	if ((new_px <0 ) || (new_py < 0) || (new_px >=  2 * radus + 1) || (new_py >= 2 * radus + 1)) {
		throw 0;
	}

	return (grid(new_py,new_px));
}


std::vector<std::pair<int, int>> Cercle::draw() {
	std::vector<std::pair<int, int>> vec;
	std::vector<std::pair<int, int>> vtmp;
	boost::numeric::ublas::matrix<int> grid(radus*2+1, radus*2+1, 0);
	vec = draw_cercle();

	//std::cout << "x size " << grid.size2() << " y size : " << grid.size1() << std::endl;

	for(auto elem : vec){
		set_pos_grid(grid, elem.first, elem.second,1);
	}

	std::stack <std::pair<int,int>> stk;
	if(get_pos_grid(grid, center.getPosX(),center.getPosY()) == 1){
		return (vec);
	}

	stk.push(std::make_pair(center.getPosX(),center.getPosY()));

	while(!stk.empty()){
		std::pair<int,int> pix = stk.top();
		stk.pop();
		//break;
		set_pos_grid(grid, pix.first,pix.second,1);
		if(get_pos_grid(grid, pix.first+1 ,pix.second  ) == 0) stk.push(std::make_pair(pix.first+1 , pix.second   ));
		if(get_pos_grid(grid, pix.first-1 ,pix.second  ) == 0) stk.push(std::make_pair(pix.first-1 , pix.second   ));
		if(get_pos_grid(grid, pix.first   ,pix.second+1) == 0) stk.push(std::make_pair(pix.first   , pix.second+1 ));
		if(get_pos_grid(grid, pix.first   ,pix.second-1) == 0) stk.push(std::make_pair(pix.first   , pix.second-1 ));
	}

	for (int j = 0; j < grid.size1(); j++) {
		for (int i = 0; i < grid.size2(); i++) {
			if(grid(i,j) == 1){
				int npx = center.getPosX() + ( - (radus+1) + i ) +1;
				int npy = center.getPosY() + ( - (radus+1) + j ) +1;
				vec.push_back(std::make_pair(npx,npy));
			}
		}
	}


	// remove duplicated
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	return (vec);
}

} /* namespace mpal */
