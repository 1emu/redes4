/*
 * Configuration.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jp
 */

#include "Configuration.h"

using namespace std;

void Configuration::addConfiguration(const string& key, const string& value) {
	this->configuration.insert(pair<string, string>(key, value));
}

bool Configuration::shouldKeepReading(const string& line) {
	return line[0] != '#' && line[0] != ';' && !line.empty();
}

Configuration::Configuration(string fileName){
	char * row = (char*) malloc(sizeof (char)* MAX_LINE_LENGTH);
	string line, key, value;
	ifstream file(fileName.c_str());
	if(file.is_open()){
		while(!file.eof()){
			file.getline(row, MAX_LINE_LENGTH);
			line = trim(string(row));
			if (shouldKeepReading(line)) {
				key = trim(line.substr(0, line.find('=')));
				value = trim(line.substr(line.find('=')).erase(0, 1));
				if (!key.empty())
					addConfiguration(key, value);
			}
		}
		free(row);
	}
}

string Configuration::get(string key){
	map<string, string>::iterator i = configuration.find(key);
	if(i != configuration.end()){
		return i->second;
	}
	return "";
}

string Configuration::trim(string stringToBeTrimmed){
	string::iterator lend, rbegin;
	string::reverse_iterator rrbegin;
	lend = find_if(stringToBeTrimmed.begin(), stringToBeTrimmed.end(), not1(ptr_fun<int, int>(isspace)));
	stringToBeTrimmed.erase(stringToBeTrimmed.begin(), lend);
	rrbegin = find_if(stringToBeTrimmed.rbegin(), stringToBeTrimmed.rend(), not1(ptr_fun<int, int>(isspace)));
	rbegin = rrbegin.base();
	stringToBeTrimmed.erase(rbegin, stringToBeTrimmed.end());
	return stringToBeTrimmed;
}

