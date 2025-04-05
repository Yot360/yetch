#include "SystemInfo.h"
#include <vector>

// Utility function to run a command from bash and return its result as a string
std::string SystemInfo::runCommand(const char *command) {
	std::array<char, 128> buffer;
	std::string result;

	FILE *pipe = popen(command, "r"); // Run command
	if (!pipe) {
		return "Error opening pipe";
	}

	// Reads command output and write it to a string
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

// Utility function to split a string into a vector using a character as the delimiter
std::vector<std::string> SystemInfo::split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

// Get the CPU info as a struct, including its name and its core count
CPUInfo SystemInfo::getCPUInfo() {
	std::ifstream cpuinfo("/proc/cpuinfo");
	std::string line;
	CPUInfo cpu_info;
	cpu_info.model_name = "Unknown CPU";
	cpu_info.processors = 0;

	// Reads /proc/cpuinfo file to find CPU info
	while (std::getline(cpuinfo, line)) {
		if (line.find("model name") != std::string::npos) {
			cpu_info.model_name = line.substr(line.find(":") + 2); // Get text after the colon and two more chars
		}
		if (line.substr(0, 9) == "processor"){
			cpu_info.processors += 1;
		}
	}
	return cpu_info;
}

// Get RAM info as a struct, including used memory and total memory
RAMInfo SystemInfo::getRAMInfo()
{
	std::ifstream meminfo("/proc/meminfo");
	std::string line;
	RAMInfo ram_info;
	unsigned long memTotalKB;
	ram_info.total = "Unknown";
	ram_info.used = "Unknown";

	// Reads /proc/meminfo file to find RAM info
	while (std::getline(meminfo, line)){
		if (line.find("MemTotal") != std::string::npos) { // Checks if the current line has total memory info
			size_t pos = line.find(":");
			if (pos != std::string::npos){
				std::string ram = line.substr(pos + 1);
				ram.erase(0, ram.find_first_not_of(" ")); // Searches the line for the first character that does not match " "
				size_t kb_pos = ram.find("kB");
				if (kb_pos != std::string::npos){
					ram.erase(kb_pos);
				}

				memTotalKB = std::stoll(ram); // Converts ram string to an unsigned long
				int ramMB = static_cast<int>(memTotalKB)/1000; // Converts the RAM count from KB to MB
				ram_info.total = std::to_string(ramMB) + "MB";
			}
		}
		if (line.find("MemFree") != std::string::npos) { // Checks if the current line has free memory info
			size_t pos = line.find(":");
			if (pos != std::string::npos){
				std::string ram = line.substr(pos + 1);
				ram.erase(0, ram.find_first_not_of(" ")); // Searches the line for the first character that does not match " "
				size_t kb_pos = ram.find("kB");
				if (kb_pos != std::string::npos){
					ram.erase(kb_pos);
				}
				long ramKB = memTotalKB - std::stoll(ram); // Converts ram string to an unsigned long and calculate used ram by doing total - used
				int ramMB = static_cast<int>(ramKB)/1000;
				ram_info.used = std::to_string(ramMB) + "MB";
			}
		}
	}
	return ram_info;
}

// Get GPU name
std::string SystemInfo::getGPU()
{
	return runCommand("lspci | grep -E -i '(Display|3D|VGA)'");
}

// Get system uptme since boot, returns a struct including hours and minutes elapsed
Time SystemInfo::getUptime()
{
	Time uptime;

	std::string result = runCommand("uptime");

	// Split the command result correctly to then parse hours and minutes
	std::vector<std::string> v = split(result, ' ');
	v[3].erase(v[3].length()-1, 1);
	std::vector<std::string> time = split(v[3], ':');

	// Converts hours and minutes strings to int
	uptime.hours = std::stoi(time[0]);
	uptime.minutes = std::stoi(time[1]);

	return uptime;
}

// Get the shell the user running yetch uses
std::string SystemInfo::getShell()
{
	std::string shell = runCommand("echo $SHELL");
	std::vector<std::string> v = split(shell, '/'); // Split the command result to just get the shell name instead of the full path
	return v[v.size()-1]; // Get last item, aka shell name, and returns it
}
