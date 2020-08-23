/*
 * EnvDrawArea.h
 *
 *  Created on: 11 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef ENVDRAWAREA_H_
#define ENVDRAWAREA_H_

#include "Environment.h"
#include "MainWindow.h"
#include "Observer.h"
#include <gtkmm-3.0/gtkmm.h>



#include "Data.h"

#include <chrono>
#include <thread>

namespace mpal {

class MainWindow;

class EnvDrawArea: public Gtk::DrawingArea, public Observer<Data> {
private:
	int width_surface;
	int height_surface;

	Environment *env = nullptr;
	AlgoType algo_type;
	Lidar *lidar_ptr  = nullptr;

	std::vector<Angle> *lst_angles_paths;
	std::vector<std::pair<int,int>> *list_waypoints;
	std::vector<Line> *lst_scan_lines;


	std::vector<std::pair<int, int>> *lst_vertex;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> *lst_adge;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;


	void draw_grid_cell(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_cell(const Cairo::RefPtr<Cairo::Context> &cr, int, int);

	void draw_a_star(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_rrtstar(const Cairo::RefPtr<Cairo::Context> &cr);

	void draw_dpath(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_obstacles(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_start_pos(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_end_pos(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_robot_pos(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_lidar_scan(const Cairo::RefPtr<Cairo::Context> &cr);

	void draw_angles(const Cairo::RefPtr<Cairo::Context> &cr);




public:
	EnvDrawArea(BaseObjectType *cobject,
			const Glib::RefPtr<Gtk::Builder> &builder);

	void refresh(Event<Data> *e) {
		Data s = *e->getInfo();
		algo_type = s.algo_type;
		env = s.env;
		lidar_ptr = s.lidar;
		lst_vertex = s.lst_vertex;
		lst_adge = s.lst_adge;
		lst_angles_paths = s.lst_angles_paths;
		list_waypoints = s.list_waypoints;
		lst_scan_lines = s.lst_scan_lines;
		delete e;

		queue_draw();
		GMainContext *context;
		context = g_main_context_default();
		while (g_main_context_iteration(context, false)){};
		usleep(5);
	}

	virtual ~EnvDrawArea();

};

} /* namespace mpal */

#endif /* ENVDRAWAREA_H_ */
