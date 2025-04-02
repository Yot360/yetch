#include <iostream>
#include "SystemInfo.h"
int main(int argc, char *argv[])
{
	std::cout << "Hello" << std::endl;
	std::cout << "CPU: " << SystemInfo::getCPUName() << std::endl;
	std::cout << "RAM: " << SystemInfo::getTotalRAM() << std::endl;
	return 0;
}
