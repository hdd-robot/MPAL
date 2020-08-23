/*
 * GraphDrawArea.h
 *
 *  Created on: 11 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef GRAPHDRAWAREA_H_
#define GRAPHDRAWAREA_H_

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <graphviz/gvc.h>
#include "Data.h"
#include "Observer.h"
#include "Environment.h"
#include "Observer.h"
#include "AlgoNav.h"

#include <boost/graph/graphviz.hpp>




namespace mpal {

class GraphDrawArea: public Gtk::DrawingArea, public Observer<Data> {
private:
	void clear_area(const Cairo::RefPtr<Cairo::Context> &cr);

	int width_surface;
	int height_surface;
	AlgoType algo_type;
	Graph* pgraph;
	Environment *env = nullptr;
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

	void draw_grid_cell(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_a_star(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_rrtstar(const Cairo::RefPtr<Cairo::Context> &cr);
	void draw_dpath(const Cairo::RefPtr<Cairo::Context> &cr);


public:
	GraphDrawArea(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

	virtual ~GraphDrawArea();


	void refresh(Event<Data> *e) {
		Data s = *e->getInfo();
		algo_type = s.algo_type;
		pgraph = s.graph;
		env = s.env;
		delete e;
		queue_draw();
		GMainContext *context;
		context = g_main_context_default();
		while (g_main_context_iteration(context, false)){};
		usleep(5);
	}

};

} /* namespace mpal */

#endif /* GRAPHDRAWAREA_H_ */
