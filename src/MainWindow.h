/*
 * MainWindow.h
 *
 *  Created on: 10 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>

#include <iostream>
#include <utility>
#include <vector>
#include "EnvDrawArea.h"
#include "GraphDrawArea.h"
#include "Planner.h"
#include "Environment.h"
#include "EnvironmentContinue.h"
#include "EnvironmentCell.h"

namespace mpal {

class EnvDrawArea;

class MainWindow: public Gtk::Window {
private:
	int width = 0;
	int height = 0;

public:
	MainWindow();
	virtual ~MainWindow();
	Gtk::Window* GetMainWindow();

	Environment *env;

protected:

	Glib::RefPtr<Gtk::Builder> m_refBuilder;
	Gtk::Window *m_main_window;

	Gtk::ToolButton *m_button_init, *m_button_refresh, *m_select_algo,
			*run_astar, *run_rrt_star, *m_button_d_nav, *toto;

	//Dialog box init
	Gtk::Button *dialog_init_button_ok, *dialog_init_button_calncel;
	Gtk::Dialog *dialog_init;
	Gtk::Entry *dialog_init_entry_height, *dialog_init_entry_width;

	EnvDrawArea *envArea;
	GraphDrawArea *graphArea;

	bool on_click_area_event(GdkEventButton*);

	void on_tool_init();
	void on_tool_refresh();

	void on_doalog_ok();
	void on_doalog_cancel();

	void on_tool_run_astar();
	void on_tool_run_rrtstar();
	void on_tool_select_algo();
	void on_tool_run_d_nav();
	void on_toto();

};

} /* namespace mpal */

#endif /* MAINWINDOW_H_ */
