#include "FileReader.h"

Core::FileReader::FileReader()
{
}

Core::FileReader::FileReader(const std::string & _filePath)
{
	SetFilePath(_filePath);
}


Core::FileReader::~FileReader()
{
}

void Core::FileReader::SetFilePath(const std::string & _filePath)
{
	m_filePath = _filePath;
}

void Core::FileReader::LoadInto(LSystem & _lsystem)
{
	if (m_filePath.empty())
	{
		std::cout << "There is no file path set!" << std::endl;
		//TODO: Implement proper error system later.
	}
	else 
	{
		std::ifstream fileStream(m_filePath);
		std::string fileLine;

		std::string attrName;
		std::string attrValue;
		while (std::getline(fileStream, fileLine))
		{
			size_t attrGap = fileLine.find("\t");
			attrName = fileLine.substr(0,attrGap);
			attrValue = fileLine.substr(attrGap + 1);
			std::cout << attrName << " " << attrValue << std::endl << std::endl;

			if (attrName == "#name") {
				_lsystem.name = attrName;
			}
		}
	}
}

