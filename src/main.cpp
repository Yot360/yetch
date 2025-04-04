#include <iostream>
#include "SystemInfo.h"
int main(int argc, char *argv[])
{
	CPUInfo cpuinfo = SystemInfo::getCPUInfo();
	Time uptime = SystemInfo::getUptime();
	std::cout << "GPU: " << SystemInfo::getGPU() << std::endl;
	std::cout << "CPU: " << cpuinfo.model_name << std::endl;
	std::cout << "Cores: " << cpuinfo.processors << std::endl;
	std::cout << "RAM: " << SystemInfo::getTotalRAM() << std::endl;
	std::cout << "Uptime: " << uptime.hours << " hours and " << uptime.minutes << " minutes" << std::endl;
	return 0;
}
