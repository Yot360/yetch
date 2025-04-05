#include <iostream>
#include "SystemInfo.h"
int main(int argc, char *argv[])
{
	CPUInfo cpuinfo = SystemInfo::getCPUInfo();
	Time uptime = SystemInfo::getUptime();
	RAMInfo raminfo = SystemInfo::getRAMInfo();
	std::cout << "GPU: " << SystemInfo::getGPU() << std::endl;
	std::cout << "CPU: " << cpuinfo.model_name << std::endl;
	std::cout << "Cores: " << cpuinfo.processors << std::endl;
	std::cout << "RAM: " << raminfo.used << "/" << raminfo.total << std::endl;
	std::cout << "Uptime: " << uptime.hours << " hours and " << uptime.minutes << " minutes" << std::endl;
	std::cout << "Shell: " << SystemInfo::getShell() << std::endl;
	return 0;
}
