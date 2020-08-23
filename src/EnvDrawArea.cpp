/*
 * EnvDrawArea.cpp
 *
 *  Created on: 11 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "EnvDrawArea.h"
#include "MainWindow.h"
#include <iostream>
namespace mpal {

EnvDrawArea::EnvDrawArea(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
		Gtk::DrawingArea(cobject) {}

void EnvDrawArea::draw_a_star(const Cairo::RefPtr<Cairo::Context> &cr) {
	draw_grid_cell(cr);
}



EnvDrawArea::~EnvDrawArea() {
	// TODO Auto-generated destructor stub
}

bool EnvDrawArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	width_surface = allocation.get_width();
	height_surface = allocation.get_height();

	switch (algo_type) {
	case AlgoType::ASTAR:
		draw_a_star(cr);
		break;
	case AlgoType::RRT_STAR:
		draw_rrtstar(cr);
		break;
	case AlgoType::D_PATH:
		draw_dpath(cr);
		break;
	default:
		break;
	}

	return (true);
}



void EnvDrawArea::draw_cell(const Cairo::RefPtr<Cairo::Context> &cr, int x, int y) {

	EnvironmentCell *env_cell = static_cast<EnvironmentCell*>(env);
	double cell_width = width_surface / env_cell->getWidth();
	double cell_height = height_surface / env_cell->getHeight();

	int displacement_x = (width_surface - (cell_width * env_cell->getWidth())) / 2;
	int displacement_y = (height_surface - (cell_height * env_cell->getHeight())) / 2;

	Cell &cell = env_cell->getCellAt(x, y);

	cr->set_source_rgb(0.37, 0.37, 0.37);
	cr->set_line_width(1);
	cr->rectangle(cell.getPosX() * cell_width + displacement_x,
			cell.getPosY() * cell_height + displacement_y, cell_width,
			cell_height);
	cr->stroke_preserve();

	switch (cell.getCellType()) {
	case CellType::FREE:
		switch (cell.getCellStatus()) {
		case CellStatus::UNEXPLORED:
			cr->set_source_rgb(1.0, 1.0, 1.0);
			break;
		case CellStatus::CALCULATED:
			cr->set_source_rgb(0.0, 0.8, 0.8);
			break;
		case CellStatus::EXPLORED:
			cr->set_source_rgb(0.8, 0.34, 1.0);
			break;
		case CellStatus::PATH:
			cr->set_source_rgb(1.0, 0.0, 0.0);
			break;
		}

		break;
	case CellType::OBSTACLE:
		cr->set_source_rgb(0.0, 0.0, 0.0);
		break;

	case CellType::START:
		cr->set_source_rgb(0.0, 1.0, 0.32);
		break;

	case CellType::GOAL:
		cr->set_source_rgb(0.99, 0.07, 0.87);
		break;

	case CellType::ROBOT:
		cr->set_source_rgb(0.0, 1.0, 0.70);
		break;
	}
	cr->fill();

	cr->stroke();
}

void EnvDrawArea::draw_grid_cell(const Cairo::RefPtr<Cairo::Context> &cr) {

	if (env == nullptr) {
		return;
	}

	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, width_surface, height_surface);
	cr->fill();

	cr->set_line_width(0.1);
	cr->set_source_rgb(1.0, 0.0, 0.0);

	for (int i = 0; i < env->getWidth(); i++) {
		for (int j = 0; j < env->getHeight(); j++) {
			draw_cell(cr, i, j);
		}
	}
	cr->stroke();
}

void EnvDrawArea::draw_rrtstar(const Cairo::RefPtr<Cairo::Context> &cr) {
	cr->set_source_rgb(0.9, 0.9, 0.9);
	cr->rectangle(0, 0, width_surface, height_surface);
	cr->fill();
	cr->stroke();

	if (env == nullptr) {
		return;
	}

	// Draw vetrices

	cr->set_line_width(0.1);
	cr->set_source_rgb(1.0, 0.0, 0.0);
	for (auto elem : *lst_vertex) {
		cr->arc(elem.first, elem.second, 5.0, 0.0, 2.0 * M_PI);
		cr->fill();
		cr->stroke();
	}

	// draw adges
	cr->set_source_rgb(0.0, 0.0, 0.0);

	for (auto elem : *lst_adge) {
		int px1 = elem.first.first;
		int py1 = elem.first.second;
		int px2 = elem.second.first;
		int py2 = elem.second.second;

		cr->set_line_width(1);
		cr->move_to(px1, py1);
		cr->line_to(px2, py2);
		cr->stroke();
	}

	// draw start and goal
	cr->set_source_rgb(0.0, 1.0, 0.0);
	cr->arc(env->getStartPosX(), env->getStartPosY(), 5.0, 0.0, 2.0 * M_PI);
	cr->fill();
	cr->stroke();

	cr->set_source_rgb(0.0, 0.0, 1.0);
	cr->arc(env->getGoalPosX(), env->getGoalPosY(), 5.0, 0.0, 2.0 * M_PI);
	cr->fill();

	cr->stroke();
}


void EnvDrawArea::draw_angles(const Cairo::RefPtr<Cairo::Context> &cr) {
	int rad = 50;
	for (auto elem : *lst_angles_paths) {
		cr->arc(env->getRobotPosX(), env->getRobotPosY(), rad, 2*M_PI - elem.teta_max, 2*M_PI-elem.teta_min);
		rad = rad + 10;
		cr->stroke();
	}


}


void EnvDrawArea::draw_dpath(const Cairo::RefPtr<Cairo::Context> &cr) {

	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->rectangle(0, 0, width_surface, height_surface);
	cr->fill();
	cr->stroke();

	draw_obstacles(cr);

	draw_lidar_scan(cr);

	draw_angles(cr);

	draw_robot_pos(cr);
	draw_start_pos(cr);
	draw_end_pos(cr);

}



void EnvDrawArea::draw_obstacles(const Cairo::RefPtr<Cairo::Context> &cr) {

	cr->set_source_rgb(0.0, 0.0, 0.0);
	cr->set_line_width (1);
	for(auto obs : env->getLstObstacles()){
		Line* line = dynamic_cast<Line*>(obs);
		if(line != nullptr){
			cr->move_to(line->getPointStart().getPosX(),line->getPointStart().getPosY());
			cr->line_to(line->getPointEnd().getPosX(),line->getPointEnd().getPosY());
		}

		Cercle* cercle = dynamic_cast<Cercle*>(obs);
		if(cercle != nullptr){
			cr->arc(cercle->getCenter().getPosX(),cercle->getCenter().getPosY(), cercle->getRadus(), 0.0, 2 * M_PI);
			//cr->fill();
		}
	}

	cr->stroke();
}

void EnvDrawArea::draw_start_pos(const Cairo::RefPtr<Cairo::Context> &cr) {
	cr->set_source_rgb(0.99, 0.07, 0.87);
	cr->arc(env->getStartPosX(),env->getStartPosY(),5.0, 0.0, 2 * M_PI);
	cr->fill();
	cr->stroke();
}

void EnvDrawArea::draw_end_pos(const Cairo::RefPtr<Cairo::Context> &cr) {
	cr->set_source_rgb(0.0, 1.0, 0.32);
	cr->arc(env->getGoalPosX(),env->getGoalPosY(),5.0, 0.0, 2 * M_PI);
	cr->fill();
	cr->stroke();
}

void EnvDrawArea::draw_robot_pos(const Cairo::RefPtr<Cairo::Context> &cr){
	cr->set_source_rgb(0.0, 1.0, 0.70);
	cr->arc(env->getRobotPosX(),env->getRobotPosY(),5.0, 0.0, 2 * M_PI);
	cr->fill();
	cr->stroke();
}


void EnvDrawArea::draw_lidar_scan(const Cairo::RefPtr<Cairo::Context> &cr) {
	cr->set_source_rgb(0.0, 0.32, 1.0);

	std::vector<Line>::iterator it = (*lst_scan_lines).begin();
	for(;it != (*lst_scan_lines).end(); it++){
		cr->move_to(it->getPointStart().getPosX(),it->getPointStart().getPosY());
		cr->line_to(it->getPointEnd().getPosX(),it->getPointEnd().getPosY());
		cr->stroke();
	}

	/**
	 * Draw Way Point
	 */
	cr->set_source_rgb(1.0, 0.0, 0.0);
	std::vector<std::pair<int,int>>::iterator it_wp = (*list_waypoints).begin();
	for(;it_wp != (*list_waypoints).end(); it_wp++){

		cr->arc(it_wp->first,it_wp->second,2.0, 0.0, 2 * M_PI);
		cr->stroke();
	}



	cr->stroke();
}



} /* namespace mpal */













