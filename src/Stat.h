/*
 * Stat.h
 *
 *  Created on: 9 juil. 2020
 *      Author: hdd
 */
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>


#ifndef SRC_STAT_H_
#define SRC_STAT_H_

namespace mpal {

class Stat {
public:
	Stat(std::string);
	virtual ~Stat();
	void addline();

private:
	std::string file_name;
	std::string sec_number;
	std::string algo_type;

	void create_file();

	std::string gen_random(const int len);
};

} /* namespace mpal */

#endif /* SRC_STAT_H_ */
