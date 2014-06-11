/*
 * Utils.h
 *
 *  Created on: May 2, 2014
 *      Author: jp
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "Includes.h"

class Utils {
public:
	Utils();
	virtual ~Utils();

	static std::string intToString(int i);

	static int generateRandomNumberBetween(unsigned int min, unsigned int max);

	static void writeout(std::string s);

	static void writeerr(std::string s);

	static void swriteout(std::stringstream &stream);

	static void swriteerr(std::stringstream &stream);

};

#endif /* UTILS_H_ */
