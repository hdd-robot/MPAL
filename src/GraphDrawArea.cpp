/*
 * GraphDrawArea.cpp
 *
 *  Created on: 11 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "GraphDrawArea.h"

namespace mpal {

GraphDrawArea::GraphDrawArea(BaseObjectType *cobject,
		const Glib::RefPtr<Gtk::Builder> &builder) :
		Gtk::DrawingArea(cobject) {
}

GraphDrawArea::~GraphDrawArea() {
	// TODO Auto-generated destructor stub
}

bool GraphDrawArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
	clear_area(cr);
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


void GraphDrawArea::draw_grid_cell(const Cairo::RefPtr<Cairo::Context> &cr) {
}

void GraphDrawArea::draw_a_star(const Cairo::RefPtr<Cairo::Context> &cr) {
}

void GraphDrawArea::draw_rrtstar(const Cairo::RefPtr<Cairo::Context> &cr) {
}

void GraphDrawArea::draw_dpath(const Cairo::RefPtr<Cairo::Context> &cr) {
	clear_area(cr);

	std::string dot = pgraph->trace_graph();

	std::cout << "DOT : " << std::endl << dot.c_str() << std::endl;


	dot = " graph mon_graphe { a -- b -- c; b -- d; } ";
	if (dot.size() == 0){
		return;
	}

	GVC_t *gvc;
	Agraph_t *g;


	std::FILE* tmpf = std::fopen("dot.dot","r");
	std::fputs(dot.c_str(), tmpf);

	gvc = gvContext ();
	g=agread(tmpf,0);

	gvLayout (gvc, g, "dot");


	gvRenderFilename(gvc, g, "png", "out.png");

	agclose (g);
	gvFreeContext(gvc);

	// draw png
	Glib::RefPtr<Gdk::Pixbuf> m_image = Gdk::Pixbuf::create_from_file("out.png");

	Gdk::Cairo::set_source_pixbuf(cr, m_image,0,0);
	cr->rectangle(0, 0, width_surface,height_surface);
	cr->fill();

}

void GraphDrawArea::clear_area(const Cairo::RefPtr<Cairo::Context> &cr) {
	//draw wihte area
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->set_line_width(1);
	cr->rectangle(0,0,width_surface,height_surface);
	cr->fill();
	cr->stroke();
}

} /* namespace mpal */
