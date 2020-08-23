#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

#include "Environment.h"
#include "EnvironmentContinue.h"
#include "EnvironmentCell.h"
#include "MainWindow.h"
#include "Line.h"
#include "AlgoAStar.h"
#include "Planner.h"
#include "Obstacle.h"

using namespace mpal;

int main(int argc, char *argv[]) {

	if (argc == 2) {
		Gtk::Main kit(argc, argv);
		MainWindow mainWindow;

		Gtk::Window *win = mainWindow.GetMainWindow();
		Gtk::Main::run((*win));
		return (0);
	}


	Environment *env;
	env = new EnvironmentContinue(200, 200);  // fuite mémoire


	Cercle c1(Point(30, 70), 19);
	env->add_obstacle(static_cast<Obstacle*>(&c1));

	Cercle c2(Point(70, 30), 20);
	env->add_obstacle(static_cast<Obstacle*>(&c2));

	Line l1(Point(41, 41), Point(91, 41));
	env->add_obstacle(static_cast<Obstacle*>(&l1));

	Line lx1 = Line(Point(0,0),Point(0,199));
	Line lx2 = Line(Point(199,0),Point(199,199));
	Line lx3 = Line(Point(199,199),Point(0,199));
	Line lx4 = Line(Point(0,0),Point(199,0));

	env->add_obstacle(static_cast<Obstacle*>(&lx1));
	env->add_obstacle(static_cast<Obstacle*>(&lx2));
	env->add_obstacle(static_cast<Obstacle*>(&lx3));
	env->add_obstacle(static_cast<Obstacle*>(&lx4));

	Planner planner(env);
	planner.setAlgotype(AlgoType::D_PATH);
	planner.run();



	return (0);
}

