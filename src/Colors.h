/*
 * Colors.h
 *
 *  Created on: May 2, 2014
 *      Author: jp
 */

#ifndef COLORS_H_
#define COLORS_H_

#include "Includes.h"
#include "Utils.h"

#define BLACK       "0;30"
#define BLUE        "0;34"
#define GREEN       "0;32"
#define CYAN        "0;36"
#define RED         "0;31"
#define PURPLE      "0;35"
#define YELLOW      "0;33"
#define WHITE       "0;37"
#define DARKGRAY     "1;30"
#define LIGHTBLUE    "1;34"
#define LIGHTGREEN   "1;32"
#define LIGHTCYAN    "1;36"
#define LIGHTRED     "1;31"
#define LIGHTPURPLE  "1;35"
#define LIGHTYELLOW  "1;33"
#define LIGHTWHITE   "1;37"
#define UNDERLINEDBLACK       "4;30"
#define UNDERLINEDBLUE        "4;34"
#define UNDERLINEDGREEN       "4;32"
#define UNDERLINEDCYAN        "4;36"
#define UNDERLINEDRED         "4;31"
#define UNDERLINEDPURPLE      "4;35"
#define UNDERLINEDYELLOW      "4;33"
#define UNDERLINEDWHITE       "4;37"

class Colors {
public:
	Colors();
	virtual ~Colors();
	static void writeout(std::string message, const char* color);
	static void writeerr(std::string message, const char* color);
private:
	static std::string colorMessage(std::string message, const char* color);
};

#endif /* COLORS_H_ */
