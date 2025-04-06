#include <iostream>
#include "SystemInfo.h"
int main(int argc, char *argv[])
{
	const CPUInfo cpuinfo = SystemInfo::getCPUInfo();
	const Time uptime = SystemInfo::getUptime();
	const RAMInfo raminfo = SystemInfo::getRAMInfo();
	const HostInfo hostinfo = SystemInfo::getHostInfo();
	const std::string gpu = SystemInfo::getGPU();
	const std::string shell = SystemInfo::getShell();
	const std::string distro = SystemInfo::getDistro();
	const std::string kernel = SystemInfo::getKernel();

	std::cout << "╭──[" << hostinfo.username << "@" << hostinfo.hostname << "]──c" << std::endl;
	std::cout << "│     .--.           " << distro << std::endl;
	std::cout << "│    |o_o |        󱙤  " << kernel << std::endl;
	std::cout << "│    |:_/ |          " << shell << std::endl;
	std::cout << "│   //   \\ \\         " << cpuinfo.model_name << std::endl;
	std::cout << "│  (|     | )        " << gpu << std::endl;
	std::cout << "│ /'\\_   _/`\\        " << raminfo.used << "MB/" << raminfo.total << "MB (" << raminfo.percentage << "%)" << std::endl;
	std::cout << "│ \\___)=(___/        " << uptime.hours << " hours and " << uptime.minutes << " minutes" << std::endl;
	std::cout << "╰──────────────────────────c" << std::endl;
	return 0;
}
