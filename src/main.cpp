#include <iostream>
#include "SystemInfo.h"
#include "Colors.h"

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

	std::cout << "╭──[" << BRIGHT_RED << hostinfo.username << RESET << "@" << BRIGHT_RED << hostinfo.hostname << RESET << "]──c" << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << "     .--.         "<< BRIGHT_CYAN << "  " << RESET << distro << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << "    |o_o |        "<< BRIGHT_CYAN << "󱙤  " << RESET << kernel << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << "    |:_/ |        "<< BRIGHT_CYAN << "  " << RESET << shell << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << "   //   \\ \\       "<< BRIGHT_CYAN << "  " << RESET << cpuinfo.model_name << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << "  (|     | )      "<< BRIGHT_CYAN << "  " << RESET << gpu << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << " /'\\_   _/`\\      "<< BRIGHT_CYAN << "  " << RESET << raminfo.used << "MB/" << raminfo.total << "MB (" << raminfo.percentage << "%)" << std::endl;
	std::cout << "│" << BRIGHT_YELLOW << " \\___)=(___/      "<< BRIGHT_CYAN << "  " << RESET << uptime.hours << " hours and " << uptime.minutes << " minutes" << std::endl;
	std::cout << "╰──────────────────────────c" << std::endl;
	return 0;
}
