#include "ConfigFile.hpp"
#include <iostream>

std::string ConfigFile::FolderName = "map1";
std::multimap<std::string, std::string> ConfigFile::MapdataFile;
void ConfigFile::setMap(){

	std::ifstream startlevel("map1/mapdata.imba");
	std::string command;
	std::string value;
	


	while (!startlevel.eof()) {
		command = "";
		value = "";
		char currentLine[256];
		startlevel.getline(currentLine, sizeof(currentLine));

		

		value.append(currentLine);

		if (value.empty()) {
			continue;
		}

		if (value[0] == '/' && value[1] == '/'){
			continue;
		}

		std::size_t begin = value.find_first_of(":");
		std::size_t end   = value.find_last_of(";");
		std::size_t len   = end - begin;
		
		
		

		command = value.substr(0, begin);
		value = value.substr(begin + 2, len - 2);

		MapdataFile.insert(std::pair<std::string, std::string>(command, value));
	}
}

std::string ConfigFile::getValue(std::string command){
	 
	if (MapdataFile.find(command) == MapdataFile.end()) {
		std::cout << "Command not Found: " << command.c_str() << std::endl;
		return "";
	}

	return MapdataFile.find(command)->second;
}

