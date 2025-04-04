#include "SystemInfo.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>

std::string SystemInfo::runCommand(const char* command)
{
	std::array<char, 128> buffer;
	std::string result;

	FILE* pipe = popen(command, "r");
	if (!pipe) {
		return "Error opening pipe";
	}

	while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
		std::string line = buffer.data();
        if (!line.empty() && line.back() == '\n') {
            line.pop_back(); // Remove the last character if it's '\n'
        }
		result += line;
	}

	pclose(pipe);

	return result;
}

std::vector<std::string> SystemInfo::split (const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

CPUInfo SystemInfo::getCPUInfo() {
	std::ifstream cpuinfo("/proc/cpuinfo");
	std::string line;
	CPUInfo cpu_info;
	cpu_info.model_name = "Unknown CPU";
	cpu_info.processors = 0;
	while (std::getline(cpuinfo, line)) {
		if (line.find("model name") != std::string::npos) {
			cpu_info.model_name = line.substr(line.find(":") + 2);
		}
		if (line.substr(0, 9) == "processor"){
			cpu_info.processors += 1;
		}
	}
	return cpu_info;
}

std::string SystemInfo::getTotalRAM()
{
	std::ifstream raminfo("/proc/meminfo");
	std::string line;
	if (std::getline(raminfo, line)){
		size_t pos = line.find(":");
		if (pos != std::string::npos){
			std::string ram = line.substr(pos + 1);
			ram.erase(0, ram.find_first_not_of(" "));
			size_t kb_pos = ram.find("kB");
			if (kb_pos != std::string::npos){
				ram.erase(kb_pos);
			}

			long ramKB = std::stoll(ram);
			int ramGB = static_cast<int>(ramKB)/1000000;

			return std::to_string(ramGB) + "GB";
		}
	}
	return "Unknown RAM";
}

std::string SystemInfo::getGPU()
{
	return runCommand("lspci | grep -E -i '(Display|3D|VGA)'");
}

Time SystemInfo::getUptime()
{
	Time uptime;

	std::string result = runCommand("uptime");

	std::vector<std::string> v = split(result, ' ');
	v[3].erase(v[3].length()-1, 1);
	std::vector<std::string> time = split(v[3], ':');

	uptime.hours = std::stoi(time[0]);
	uptime.minutes = std::stoi(time[1]);

	return uptime;
}
