/*
 * Configuration.h
 *
 *  Created on: Jun 13, 2014
 *      Author: jp
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Includes.h"

using namespace std;

class Configuration {
private:
    map<string, string> configuration;
    static const int MAX_LINE_LENGTH = 256;

public:
	Configuration(string fileName);
    string get(string key);

private:
    void read(string fileName);
    string trim(string string);
	void addConfiguration(const string& key, const string& value);
	bool shouldKeepReading(const string& line);
};

#endif /* CONFIGURATION_H_ */
