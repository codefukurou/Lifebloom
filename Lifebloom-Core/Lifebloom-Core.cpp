#include "FileReader.h"
#include "LSystem.h"

int main () 
{
	Core::FileReader fileReader("mycelis-muralis-m3.lsys");
	Core::LSystem lsystem;
	fileReader.LoadInto(lsystem);
	std::cin.get();
}