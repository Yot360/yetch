#include "SystemInfo.h"
#include <cstdio>

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
	std::array<char, 128> buffer;
	std::string result;

	FILE* pipe = popen("lspci | grep -E -i '(Display|3D|VGA)'", "r");
	if (!pipe) {
		return "Error opening pipe";
	}

	while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
		result += buffer.data();
	}

	pclose(pipe);

	return result;
}
