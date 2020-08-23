/*
 * Graph.h
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>

#include <boost/graph/adjacency_iterator.hpp>


#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/grid_graph.hpp>

#include <boost/graph/graphviz.hpp>
#include <vector>
#include <iostream>

#include "Cell.h"

namespace mpal {

enum class VertexType {
	START, GOAL, NORMAL, VISITED, UNVISITED, ROBOT
};

enum class EdgeType {
	NORMAL,TMP
};

struct GraphProperties {
	GraphProperties() {
	}
};

struct EdgeProperties {
	double weight;
	double distance;
	double distancetmp;
	int id_v1;
	int id_v2;
	EdgeType type;
	EdgeProperties() :
			id_v1(0), id_v2(0), weight(0.0), distance(0.0), type(EdgeType::NORMAL) {
	}
	EdgeProperties(int v1, int v2, float w, float d, EdgeType e) :
			id_v1(v1), id_v2(v2), weight(w), distance(d), type(e) {
	}
};

struct VertexProperties {
	int id;
	int pos_x;
	int pos_y;

	double g;
	double h;

	double gtmp;
	double htmp;

	int pred = 0;

	VertexType v_type;
	Cell *cell;
	VertexProperties() :
			id(0), pos_x(0), pos_y(0), v_type(VertexType::NORMAL), cell(nullptr), g(0), h(0) {
	}

	VertexProperties(int i, Cell *cel, int x, int y, VertexType vt, double pg=0, double ph=0) :
			id(i), cell(cel), pos_x(x), pos_y(y), v_type(vt), g(pg), h(ph) {
	}
};





typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
		VertexProperties, EdgeProperties, GraphProperties> GraphNav;

typedef boost::graph_traits<GraphNav>::vertex_descriptor vertex_t;
typedef boost::graph_traits<GraphNav>::edge_descriptor edge_t;




class Graph {
private:

	int id = 0;
	vertex_t get_vertx_by_id(int id);

	std::vector<vertex_t> a_star();
	vertex_t a_star_remove_lowcost(std::list<vertex_t>&);


public:

	GraphNav graph_nav;

	static double eclud_dist(int, int, int, int);

	Graph();
	virtual ~Graph();

	void init();
	int add_vertex(int, int, VertexType);
	int add_vertex(int, int, VertexType, double, double);
	void add_edge(int, int, int, EdgeType typevtx=EdgeType::NORMAL);




	int get_nearast_vertex_to(std::pair<int, int>);


	// For dpath_algorithm

	int robot_pos_vtx=0;
	int start_pos_vtx=0;
	int goal_pos_vtx=0;
	int add_start_vtx(std::pair<int, int>);
	int add_goal_vtx(std::pair<int, int>);
	bool goal_is_reached();

	double eclud_dist_2_vtx(int, int);

	void trace_adges_to_target(int vtx);

	int get_next_vertex();
	int add_waypoint_vertex(std::pair<int, int>);
	int set_robot_pos(int vtx);
	///////////////////////////////////////////



	int get_pos_x(int);
	int get_pos_y(int);

	std::string trace_graph();


	std::vector<std::pair<int, int>> get_list_vertex();
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> get_list_adge();

};

} /* namespace mpal */

#endif /* GRAPH_H_ */

