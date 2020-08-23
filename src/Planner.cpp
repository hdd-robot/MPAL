/*
 * Planner.cpp
 *
 *  Created on: 12 mai 2020
 *      Author: Halim Djerroud <hdd@ai.univ-paris8.fr>
 */

#include "Planner.h"

namespace mpal {

Planner::Planner(Environment *environement) :
		env(environement) {
}
Planner::Planner(Environment *environement, Gtk::DrawingArea *envDraw) :
		env(environement), envArea(static_cast<EnvDrawArea*>(envDraw)) {
}

Planner::Planner(Environment *environement, Gtk::DrawingArea *envDraw, Gtk::DrawingArea *graphDraw) :
		env(environement), envArea(static_cast<EnvDrawArea*>(envDraw)),graphArea(static_cast<GraphDrawArea*>(graphDraw)) {
}

Planner::~Planner() {

}

void Planner::run_aStar() {
	AlgoAStar a_ast(static_cast<EnvironmentCell*>(env));
	a_ast.addObserver(envArea);
	a_ast.run();
}

void Planner::run_rrtStar() {
	AlgoRRT rrt_ast(static_cast<EnvironmentContinue*>(env));
	rrt_ast.addObserver(envArea);
	rrt_ast.run();
	lst_vertex = rrt_ast.get_vertrices();
	lst_adge = rrt_ast.get_adges();
}

void Planner::run_dStarLite() {

}

void Planner::run_dPath() {
	AlgoDPath dPath(static_cast<EnvironmentContinue*>(env));
	dPath.addObserver(envArea);
	dPath.addObserver(graphArea);
	dPath.run();

}

void Planner::run() {
	//if(valid_param() == false ) return;
	switch (algotype) {
	case AlgoType::ASTAR:
		run_aStar();
		break;
	case AlgoType::DSTARLITE:
		run_dStarLite();
		break;
	case AlgoType::DSTARCLASSIC:
		break;
	case AlgoType::RRT_STAR:
		run_rrtStar();
		break;
	case AlgoType::D_PATH:
		run_dPath();
		break;
	}

}

bool Planner::valid_param() {
	if (algotype == AlgoType::NOT_SET)
		return (false);
	if (env->getHeight() == 0)
		return (false);
	if (env->getWidth() == 0)
		return (false);
	if (env->getRobotPosX() == -1)
		return (false);
	if (env->getRobotPosY() == -1)
		return (false);
	if (env->getStartPosX() == -1)
		return (false);
	if (env->getStartPosY() == -1)
		return (false);
	if (env->getGoalPosX() == -1)
		return (false);
	if (env->getGoalPosY() == -1)
		return (false);

	if (env->getRobotPosX() == env->getGoalPosX()
			& env->getRobotPosY() == env->getGoalPosY())
		return (false);

	return (true);
}

} /* namespace mpal */
