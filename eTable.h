#ifndef ETABLE_H_
#define ETABLE_H_

#include <string>
#include <fstream>
#include <utility>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>


class eTable 
{
	private:

		std::unordered_map<std::string, std::string> _eTable;

		void add(const std::string& key, const std::string& item) { _eTable.insert(std::make_pair(key, item)); };

	public:

		eTable(){}
		void initializeTable(std::string filename);
		bool check(const std::string& key){ try { _eTable.at(key); return true; } catch (std::out_of_range) { return false; } }
		std::string get(const std::string& key){ return _eTable.at(key); };
};


#endif