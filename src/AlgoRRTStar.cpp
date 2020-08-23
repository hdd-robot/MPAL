/*
 * AlgoRRTStar.cpp
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "AlgoRRTStar.h"

namespace mpal {

AlgoRRT::AlgoRRT(EnvironmentContinue *env) :
		AlgoContEnvBased(env) {
	algoName = AlgoType::RRT_STAR;
}

AlgoRRT::~AlgoRRT() {
}

bool AlgoRRT::init() {
	graph.init();
	graph.add_vertex(environment->getStartPosX(), environment->getStartPosY(),
			VertexType::START);
	get_vertrices();
	get_adges();
	notify();
	return true;
}

bool AlgoRRT::step() {
	return true;
}

std::pair<int, int> AlgoRRT::get_random_point() {
	int x = environment->getWidth();
	int y = environment->getHeight();

	std::srand(std::time(nullptr));
	int rand_val1 = std::rand();
	int rand_val2 = std::rand();

	x = rand_val1 % x;
	y = rand_val2 % y;
	return (std::make_pair(x, y));
}

bool AlgoRRT::run() {
	init();
	int new_vtx_id;

	while (true) {
		std::pair<int, int> qNewPos = get_random_point();
		int id_vtx_qNear = graph.get_nearast_vertex_to(qNewPos);
		int dist = eclud_dist(qNewPos.first, qNewPos.second,
				graph.get_pos_x(id_vtx_qNear), graph.get_pos_y(id_vtx_qNear));
		if (dist >= distance) {
			std::pair<int, int> nextpos = get_next_pos(id_vtx_qNear,
					qNewPos.first, qNewPos.second);
			if (goal_is_reached(nextpos.first, nextpos.second)) {
				new_vtx_id = graph.add_vertex(nextpos.first, nextpos.second,
						VertexType::GOAL);
				graph.add_edge(id_vtx_qNear, new_vtx_id, distance);
				break;
			}
			new_vtx_id = graph.add_vertex(nextpos.first, nextpos.second,
					VertexType::NORMAL);
			graph.add_edge(id_vtx_qNear, new_vtx_id, distance);

			//if(i == 5){ break;}
		}

		get_vertrices();
		get_adges();
		notify();
	}

	graph.trace_graph();
	return true;

}

// return new position near_vertex + distance
std::pair<int, int> AlgoRRT::get_next_pos(int vtx_id, int rand_px,
		int rand_py) {
	std::complex<double> c1(graph.get_pos_x(vtx_id), graph.get_pos_y(vtx_id));
	std::complex<double> c2(rand_px, rand_py);
	double arg = std::arg(c2 - c1);
	std::complex<double> c3(std::polar(static_cast<double>(distance), arg));
	c3 = c3 + c1;
	return (std::make_pair<int, int>(c3.real(), c3.imag()));
}

bool AlgoRRT::goal_is_reached(int px, int py) {
	if (eclud_dist(px, py, environment->getGoalPosX(),
			environment->getGoalPosY()) <= distance) {
		return true;
	}
	return false;
}

double AlgoRRT::eclud_dist(int p1x, int p1y, int p2x, int p2y) {
	return (std::sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y)));
}

void AlgoRRT::set_distance(int dist) {
	distance = dist;
}

} /* namespace mpal */
