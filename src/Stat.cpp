/*
 * Stat.cpp
 *
 *  Created on: 9 juil. 2020
 *      Author: hdd
 */

#include "Stat.h"

namespace mpal {

Stat::Stat(std::string algoType) {
	create_file();
	algo_type = algoType;
}

Stat::~Stat() {
	// TODO Auto-generated destructor stub
}

void Stat::addline() {
	std::ofstream file(file_name);



	file.close();
}

void Stat::create_file() {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "data_%d-%m-%Y_%H:%M:%S", timeinfo);
	std::string fname(buffer);
	this->file_name = fname;
	std::ofstream file(fname);
	file.close();
}

std::string Stat::gen_random(const int len) {
		std::string rend;
	    static const char alphanum[] =
	        "0123456789"
	        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	        "abcdefghijklmnopqrstuvwxyz";

	    for (int i = 0; i < len; ++i) {
	    	rend[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	    }

	   rend[len] = 0;
	   return (rend);
	}


} /* namespace mpal */
