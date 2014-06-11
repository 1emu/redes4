/*
 * Colors.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Colors.h"

void Colors::writeout(std::string message, const char* color){
	std::string coloredMessage = colorMessage(message, color);
	Utils::writeout(coloredMessage);
}


void Colors::writeerr(std::string message, const char* color){
	std::string coloredMessage = colorMessage(message, color);
	Utils::writeerr(coloredMessage);
}

std::string Colors::colorMessage(std::string message, const char* color) {
	std::string header = "\033[";
	std::string ending = "\033[0m";
	std::string coloredMessage = header + color + "m" + message + ending;
	return coloredMessage;
}
