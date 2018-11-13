#pragma once
#include<string>
#include<vector>
#include<map>
#include "FileReader.h"

namespace Core
{
	class LSystem
	{
		friend class FileReader;
		friend class FileWriter;

	protected:
		std::string name;
		std::string type;		
		std::string axiom;
		std::map<char,std::string> includePaths;
		std::vector<std::string> rules;
		int level;

	public:
		LSystem();
		~LSystem();
	};
}


