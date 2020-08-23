/*
 * Graph.cpp
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Graph.h"

namespace mpal {

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::init() {
	id = 0;

}



int Graph::add_vertex(int x, int y, VertexType vt) {
	id++;
	vertex_t new_vertex = boost::add_vertex(VertexProperties(id, nullptr, x, y, vt,0,0), graph_nav);
	return id;
}

/**
 *
 * @param x
 * @param y
 * @param vt
 * @return
 */
int Graph::add_vertex(int x, int y, VertexType vt, double g, double h) {
	id++;
	vertex_t new_vertex = boost::add_vertex(VertexProperties(id, nullptr, x, y, vt,g,h), graph_nav);
	return id;
}

/**
 * return Id of nearest vertex
 */
int Graph::get_nearast_vertex_to(std::pair<int, int> p) {
	GraphNav::vertex_iterator vtx_near;

	std::pair<GraphNav::vertex_iterator, GraphNav::vertex_iterator> vtx_it = boost::vertices(graph_nav);
	vtx_near = vtx_it.first;

	for (; vtx_it.first != vtx_it.second; ++vtx_it.first) {
		if (eclud_dist(p.first, p.second, graph_nav[*vtx_it.first].pos_x, graph_nav[*vtx_it.first].pos_y) <
		    eclud_dist(p.first, p.second, graph_nav[*vtx_near].pos_x, graph_nav[*vtx_near].pos_y)) {
			vtx_near = vtx_it.first;
		}
	}

	return (graph_nav[*vtx_near].id);
}

/**
 *
 * @param p1x
 * @param p1y
 * @param p2x
 * @param p2y
 * @return
 */
double Graph::eclud_dist(int p1x, int p1y, int p2x, int p2y) {
	return (std::sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y)));
}

/**
 *
 * @param vtx_id
 * @return
 */
int Graph::get_pos_x(int vtx_id) {
	return (graph_nav[get_vertx_by_id(vtx_id)].pos_x);
}

/**
 *
 * @param vtx_id
 * @return
 */
int Graph::get_pos_y(int vtx_id) {
	return (graph_nav[get_vertx_by_id(vtx_id)].pos_y);
}


/**
 * \brief get vertex discreptor by ID
 * @param id_vtx
 * @return
 */
vertex_t Graph::get_vertx_by_id(int id_vtx) {

	std::pair<GraphNav::vertex_iterator, GraphNav::vertex_iterator> vtx_it =
			boost::vertices(graph_nav);

	for (; vtx_it.first != vtx_it.second; ++vtx_it.first) {
		if (graph_nav[*vtx_it.first].id == id_vtx) {
			return (*vtx_it.first);
		}
	}
	return (*vtx_it.second); // not found
}

/**
 *
 * @param v1
 * @param v2
 * @param dist
 */
void Graph::add_edge(int v1, int v2, int dist, EdgeType typevtx) {
	vertex_t vtx1 = get_vertx_by_id(v1);
	vertex_t vtx2 = get_vertx_by_id(v2);
	std::pair<GraphNav::edge_descriptor, bool> edge_tmp =
		  boost::add_edge(vtx1,vtx2, EdgeProperties(v1, v2, dist, dist, typevtx), graph_nav);
}


/**
 * \brief trace_graph
 */
std::string Graph::trace_graph() {
	std::string tmp;

	std::filebuf fb;
	fb.open ("dot.dot",std::ios::out);
	std::ostream os(&fb);


	boost::dynamic_properties dp;
	dp.property("node_id", get(&VertexProperties::id, graph_nav));
	//dp.property("label", get(&VertexProperties::htmp, graph_nav));
	//dp.property("label", get(&VertexProperties::gtmp, graph_nav));

	dp.property("label", get(&EdgeProperties::distancetmp, graph_nav));


	write_graphviz_dp(os, graph_nav, dp);
	std::stringstream ss;
	ss << os.rdbuf();
	tmp = ss.str();
	fb.close();

	std::cout << "tmp ::" << tmp << std::endl;

	return (tmp);
}


/**
 * \brief get list of vertices
 * @return
 */
std::vector<std::pair<int, int>> Graph::get_list_vertex() {
	std::vector<std::pair<int, int>> vec;
	std::pair<GraphNav::vertex_iterator, GraphNav::vertex_iterator> vtx_it = boost::vertices(graph_nav);
	for (; vtx_it.first != vtx_it.second; ++vtx_it.first) {
		vec.push_back( std::make_pair(graph_nav[*vtx_it.first].pos_x, graph_nav[*vtx_it.first].pos_y));
	}
	return (vec);
}


/**
 * return true if goal is near < 50
 * @return
 */
bool Graph::goal_is_reached() {
	vertex_t v1 = get_vertx_by_id(robot_pos_vtx);
	vertex_t v2 = get_vertx_by_id(goal_pos_vtx);
	double dst = eclud_dist(graph_nav[v1].pos_x,graph_nav[v1].pos_y,graph_nav[v2].pos_x,graph_nav[v2].pos_y);
	if(dst > 10) {
		return (false);
	}
	return (true);
}

std::vector<vertex_t> Graph::a_star() {
	std::list<vertex_t>   open_list;
	std::set<vertex_t>    close_list;
	std::vector<vertex_t> path;

	vertex_t beg = get_vertx_by_id(robot_pos_vtx);
	vertex_t end = get_vertx_by_id(goal_pos_vtx);


	graph_nav[beg].gtmp = 0;
	graph_nav[beg].htmp = eclud_dist(graph_nav[beg].pos_x,graph_nav[beg].pos_y,graph_nav[end].pos_x,graph_nav[end].pos_y);;
	graph_nav[end].htmp = 0;

	vertex_t curent_vtx;
	open_list.push_back(beg);


	while (open_list.empty() != true) {
		std::cout << "--Main While-- " << std::endl;
		curent_vtx = a_star_remove_lowcost(open_list);
		if(graph_nav[curent_vtx].v_type == VertexType::GOAL){
			break;
		}

		close_list.insert(curent_vtx);

		std::pair<GraphNav::adjacency_iterator, GraphNav::adjacency_iterator> it_next = boost::adjacent_vertices(curent_vtx, graph_nav);
		for( ; it_next.first != it_next.second; ++it_next.first){

			vertex_t elem = *it_next.first;
			if( close_list.find(elem) != close_list.end()) {
			   continue;
		   }

		   graph_nav[*it_next.first].htmp = eclud_dist(graph_nav[*it_next.first].pos_x,graph_nav[*it_next.first].pos_y,graph_nav[end].pos_x,graph_nav[end].pos_y);;



		   double dst = eclud_dist_2_vtx(graph_nav[*it_next.first].id, graph_nav[curent_vtx].id);



		   graph_nav[*it_next.first].gtmp = graph_nav[curent_vtx].gtmp + graph_nav[boost::edge(curent_vtx,*it_next.first,graph_nav).first].distance;
		   graph_nav[boost::edge(curent_vtx,*it_next.first,graph_nav).first].distancetmp = dst;
		   graph_nav[*it_next.first].pred = graph_nav[curent_vtx].id;
		   open_list.push_back(elem);



		   std::cout << "  --for- " << std::endl;
		   std::cout << " s:" << graph_nav[curent_vtx].id << std::endl;
		   std::cout << " d:" <<  graph_nav[*it_next.first].id << std::endl;
		   std::cout << " dst :  " << graph_nav[boost::edge(curent_vtx,*it_next.first,graph_nav).first].distancetmp << std::endl;

		}
	}

	std::cout << "--END Main While-- " << std::endl;


	vertex_t tmp_curent_vtx = end;
	while (graph_nav[tmp_curent_vtx].id != graph_nav[beg].id) {
		path.push_back(tmp_curent_vtx);
		tmp_curent_vtx = get_vertx_by_id(graph_nav[tmp_curent_vtx].pred);
	}


	return (path);
}

vertex_t Graph::a_star_remove_lowcost(std::list<vertex_t>& open_list) {
	std::list<vertex_t>::iterator it, it_tmp, min_vtx;
	it_tmp = open_list.begin();
	min_vtx = it_tmp;

	for (it = open_list.begin(); it != open_list.end(); it++) {
		if (graph_nav[*min_vtx].htmp + graph_nav[*min_vtx].gtmp > graph_nav[*it].htmp + graph_nav[*it].gtmp) {
			min_vtx = it;
			it_tmp = it;
		}
	}
	open_list.erase(it_tmp);
	return (*min_vtx);
}

/**
 * \brief get list of edges
 * @return
 */
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Graph::get_list_adge() {
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> vec;

	std::pair<GraphNav::edge_iterator, GraphNav::edge_iterator> edg_it = boost::edges(graph_nav);
	for (; edg_it.first != edg_it.second; ++edg_it.first) {

		int p1x = get_pos_x(graph_nav[*edg_it.first].id_v1);
		int p1y = get_pos_y(graph_nav[*edg_it.first].id_v1);
		int p2x = get_pos_x(graph_nav[*edg_it.first].id_v2);
		int p2y = get_pos_y(graph_nav[*edg_it.first].id_v2);

		vec.push_back(
				std::make_pair(std::make_pair(p1x, p1y),
						std::make_pair(p2x, p2y)));

	}
	return (vec);
}


/**
 * return equliden distance between 2 vetrices
 * @param vtx1
 * @param vtx2
 * @return
 */
double Graph::eclud_dist_2_vtx(int vtx1, int vtx2) {
	vertex_t v1 = get_vertx_by_id(vtx1);
	vertex_t v2 = get_vertx_by_id(vtx2);
	double dst = eclud_dist(graph_nav[v1].pos_x,graph_nav[v1].pos_y,graph_nav[v2].pos_x,graph_nav[v2].pos_y);
	return (dst);
}


/**
 * add vertex waypoint
 * @param pos
 * @return
 */
int Graph::add_waypoint_vertex(std::pair<int, int> pos) {

	// todo : vérifier si ya pas deja un vtx dans les environs
	int new_vtx =  add_vertex(pos.first,pos.second,VertexType::VISITED);

	double dst = eclud_dist_2_vtx(robot_pos_vtx, new_vtx);
	add_edge(robot_pos_vtx,new_vtx,dst, EdgeType::NORMAL);


	add_edge(new_vtx,goal_pos_vtx,dst, EdgeType::TMP);

	return (new_vtx);
}


void Graph::trace_adges_to_target(int vtx) {

}


int Graph::get_next_vertex() {

	std::vector<vertex_t> lst_path = a_star();

	return (graph_nav[lst_path.back()].id);

}


int Graph::add_start_vtx(std::pair<int, int> pos) {
	this->start_pos_vtx =  add_vertex(pos.first,pos.second,VertexType::START);
	this->robot_pos_vtx = start_pos_vtx;
	return(0);
}

int Graph::add_goal_vtx(std::pair<int, int> pos) {
	this->goal_pos_vtx =  add_vertex(pos.first,pos.second,VertexType::GOAL);
	return(0);

}

int Graph::set_robot_pos(int new_vtx) {
	vertex_t vtx ;
	if(vtx != 0){
		vtx = get_vertx_by_id(robot_pos_vtx);
		graph_nav[vtx].v_type = VertexType::NORMAL;
	}
	robot_pos_vtx = new_vtx;
	graph_nav[vtx].v_type = VertexType::ROBOT;
	return (new_vtx);
}



} /* namespace mpal */

