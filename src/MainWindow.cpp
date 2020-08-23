/*
 * MainWindow.cpp
 *
 *  Created on: 10 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "MainWindow.h"

namespace mpal {

MainWindow::MainWindow() {

	m_refBuilder = Gtk::Builder::create();

	m_refBuilder->add_from_file("/home/hdd/workspace_cpp/MPAL/GUI/glade_window.glade");

	m_refBuilder->get_widget("mainwindow", m_main_window);
	m_refBuilder->get_widget("init_tb", m_button_init);
	m_refBuilder->get_widget("refresh_tb", m_button_refresh);
	m_refBuilder->get_widget("init_env_db", dialog_init);
	m_refBuilder->get_widget("select_algo", m_select_algo);
	m_refBuilder->get_widget("run_astar", run_astar);
	m_refBuilder->get_widget("run_rrtstar", run_rrt_star);
	m_refBuilder->get_widget("d_nav", m_button_d_nav);

	m_refBuilder->get_widget("toto", toto);


	m_refBuilder->get_widget("ok_btn", dialog_init_button_ok);
	m_refBuilder->get_widget("cancel_btn", dialog_init_button_calncel);
	m_refBuilder->get_widget("nbr_width", dialog_init_entry_height);
	m_refBuilder->get_widget("nbr_height", dialog_init_entry_width);

	m_refBuilder->get_widget_derived("env_area", envArea);
	m_refBuilder->get_widget_derived("graph_area", graphArea);

	m_button_init->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_init));
	m_button_refresh->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_refresh));
	m_select_algo->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_select_algo));
	run_astar->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_run_astar));
	run_rrt_star->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_run_rrtstar));
	m_button_d_nav->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_tool_run_d_nav));

	toto->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_toto));



	dialog_init_button_ok->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_doalog_ok));
	dialog_init_button_calncel->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_doalog_cancel));

	envArea->signal_button_press_event().connect(sigc::mem_fun(*this, &MainWindow::on_click_area_event));

	envArea->add_events(
			Gdk::LEAVE_NOTIFY_MASK   |
			Gdk::BUTTON_PRESS_MASK   |
			Gdk::POINTER_MOTION_MASK |
			Gdk::POINTER_MOTION_HINT_MASK);
}

MainWindow::~MainWindow() {

}

Gtk::Window* MainWindow::GetMainWindow() {
	m_main_window->maximize();
	return (this->m_main_window);
}

void MainWindow::on_tool_refresh() {

	std::cout << "refresh " << std::endl;

}

void MainWindow::on_tool_init() {
	dialog_init->show();
}

void MainWindow::on_doalog_ok() {
	width = std::stoi(dialog_init_entry_width->get_text());
	height = std::stoi(dialog_init_entry_height->get_text());
}

bool MainWindow::on_click_area_event(GdkEventButton *motion_event) {
	std::cout << "Dessin1" << std::endl;
	return (true);
}

void MainWindow::on_doalog_cancel() {
	dialog_init->hide();
}

void MainWindow::on_tool_run_astar() {
	int w = 100;
	int h = 100;

	env = new EnvironmentCell(w, h);  // fuite mémoire
	env->set_goal_pos(10, 5);
	env->set_start_pos(95, 98);
	env->set_robot_pos(2, 98);

	Cercle c1(Point(20, 20), 5);
	env->add_obstacle(static_cast<Obstacle*>(&c1));

	Cercle c2(Point(70, 70), 10);
	env->add_obstacle(static_cast<Obstacle*>(&c2));

	Line l1(Point(2, 2), Point(2, 30));
	env->add_obstacle(static_cast<Obstacle*>(&l1));

	Planner planner(env, envArea);
	planner.setAlgotype(AlgoType::ASTAR);
	planner.run();
	envArea->queue_draw();

}

void MainWindow::on_tool_run_rrtstar() {
	int w = 800;
	int h = 800;

	env = new EnvironmentContinue(w, h);  // fuite mémoire
	env->set_goal_pos(100, 50);
	env->set_start_pos(795, 798);
	env->set_robot_pos(2, 98);

	Planner planner(env, envArea);
	planner.setAlgotype(AlgoType::RRT_STAR);
	planner.run();

	envArea->queue_draw();
}

void MainWindow::on_tool_run_d_nav() {
	int w = 800;
	int h = 800;
	env = new EnvironmentContinue(w, h);  // fuite mémoire
	env->set_goal_pos(10, 5);
	env->set_start_pos(500, 600);
	env->set_robot_pos(500, 600);

	//Cercle c1(Point(20, 20), 5);
	//env->add_obstacle(static_cast<Obstacle*>(&c1));

	Cercle c2(Point(270, 270), 70);
	env->add_obstacle(static_cast<Obstacle*>(&c2));

	Line lx1 = Line(Point(0,0),Point(0,w-1));
	Line lx2 = Line(Point(w-1,0),Point(w-1,w-1));
	Line lx3 = Line(Point(w-1,w-1),Point(0,w-1));
	Line lx4 = Line(Point(0,0),Point(w-1,0));

	env->add_obstacle(static_cast<Obstacle*>(&lx1));
	env->add_obstacle(static_cast<Obstacle*>(&lx2));
	env->add_obstacle(static_cast<Obstacle*>(&lx3));
	env->add_obstacle(static_cast<Obstacle*>(&lx4));


	Line l1(Point(10, 40), Point(150, 40));
	env->add_obstacle(static_cast<Obstacle*>(&l1));

	Line l2(Point(10, 180), Point(150, 180));
	env->add_obstacle(static_cast<Obstacle*>(&l2));

	Planner planner(env, envArea, graphArea);
	planner.setAlgotype(AlgoType::D_PATH);
	planner.run();

	envArea->queue_draw();
	graphArea->queue_draw();

}

void MainWindow::on_tool_select_algo() {
}


void MainWindow::on_toto() {
	std::cout << " Hello Mehdy et Alex" << std::endl;
}

} /* namespace mpal */

