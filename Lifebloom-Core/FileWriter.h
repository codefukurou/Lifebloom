#pragma once
#include "LSystem.h"

namespace Core 
{
	class FileWriter
	{
	public:
		FileWriter();
		~FileWriter();

		void LoadFrom(const Core::LSystem& lsystem);
	};
}

