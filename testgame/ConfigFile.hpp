#pragma once
#include <fstream>
#include <map>


class ConfigFile {
	static std::string FolderName;
	static std::multimap<std::string, std::string> MapdataFile;

public:
	static void setMap();
	static std::string getValue(std::string);
	



};