#include "eTable.h"

void eTable::initializeTable(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if(!file.is_open()) // File doesn't open
	{
		std::cerr << "[eTable][InitializeTable]  Invalid filename: " << filename << std::endl;
		exit(-1);
	}

	std::string line, str;
	std::vector<std::string> strVector;

	while(std::getline(file, line))
	{

		std::istringstream iss(line);

		while (iss >> str)
		{
			strVector.push_back(str);
		}

		if(strVector.size() == 0)
		{
			break; //TODO
		}else if(strVector.size() == 2){
			add(strVector.at(0), strVector.at(1));
			strVector.clear();
		}else{
			//std::cerr << "[eTable][InitializeTable]  Invalid file format: Missing/Extra Entry" << std::endl;
			exit(-1);
		}


	}
}
