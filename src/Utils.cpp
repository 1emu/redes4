/*
 * Utils.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Utils.h"

std::string Utils::intToString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

void Utils::writeout(std::string s) {
	s = s + "\n";
	write(fileno(stdout), s.c_str(), s.size());
}

void Utils::swriteout(std::stringstream &stream) {
	writeout(stream.str());
	stream.str(std::string());
}

void Utils::writeerr(std::string s) {
	s = s + "\n";
	if (write(fileno(stderr), s.c_str(), s.size())) {
	}
}

void Utils::swriteerr(std::stringstream &stream) {
	writeerr(stream.str());
	stream.str(std::string());
}

int Utils::generateRandomNumberBetween(unsigned int min, unsigned int max) {
	return (int) rand() % max + min;
}
