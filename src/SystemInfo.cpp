#include <SystemInfo.h>

std::string SystemInfo::getCPUName() {
	std::ifstream cpuinfo("/proc/cpuinfo");
	std::string line;
	while (std::getline(cpuinfo, line)) {
		if (line.find("model name") != std::string::npos) {
			return line.substr(line.find(":") + 2);
		}
	}
	return "Unknown CPU";
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
