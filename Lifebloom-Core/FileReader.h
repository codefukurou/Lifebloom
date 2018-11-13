#pragma once
#include<string>
#include <fstream>
#include <sstream>
#include <iostream>
#include"LSystem.h"


namespace Core
{
	// Forward declaration of LSystem for some reason...
	// TODO: Find more elegant solution than this...
	class LSystem;

	class FileReader
	{
	private:
		std::string m_filePath;

	public:
		FileReader();
		FileReader(const std::string &);
		~FileReader();

		void SetFilePath(const std::string & _filePath);
		void LoadInto(LSystem & _lsystem);
	};
}


