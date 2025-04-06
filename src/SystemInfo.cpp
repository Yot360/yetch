#include "SystemInfo.h"
#include <fstream>
#include <string>
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
	CPUInfo cpu_info = {"Unknown CPU", 0};

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
	RAMInfo ram_info = {0, 0, 0};
	unsigned long memTotalKB;
	unsigned long memUsedKB;

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
				ram_info.total = ramMB;
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
				memUsedKB = memTotalKB - std::stoll(ram); // Converts ram string to an unsigned long and calculate used ram by doing total - used
				int ramMB = static_cast<int>(memUsedKB)/1000;
				ram_info.used = ramMB;
			}
		}
	}

	// Calculate percentage of used ram our of total ram
	ram_info.percentage = (100*memUsedKB)/memTotalKB;

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
	Time uptime = {0, 0};
	std::ifstream uptimeF("/proc/uptime");
	std::string line;

	if (std::getline(uptimeF, line)) {
		std::vector<std::string> v = split(line, ' ');
		int totalMinutes = std::stoll(v[0])/60;
		int hours = totalMinutes/60;
		int minutes = totalMinutes % 60;
		uptime.hours = hours;
		uptime.minutes = minutes;
	}

	return uptime;
}

// Get the shell the user running yetch uses
std::string SystemInfo::getShell()
{
	std::string shell = "Unknown";
	shell = runCommand("echo $SHELL");
	std::vector<std::string> v = split(shell, '/'); // Split the command result to just get the shell name instead of the full path
	return v[v.size()-1]; // Get last item, aka shell name, and returns it
}

// Get the Linux distribution
std::string SystemInfo::getDistro()
{
	std::string distro = "Unknown";
	std::string result = runCommand("lsb_release -i");
	int npos = result.find("ID:");
	distro = result.substr(npos+4);
	return distro;
}

std::string SystemInfo::getKernel()
{
	std::string kernel;
	std::string result = runCommand("uname -a");
	std::vector<std::string> v = split(result, ' ');

	v.erase(v.begin()+1); // Removes the hostname from the result

	// Remove erything after the # from the result
	for (int i = 0; i < v.size(); i++) {
		if (v[i][0] == '#') {
			v.erase(v.begin() + i, v.end());
		}
	}

	// Remake string from vector
	for (std::string n : v) {
		kernel.append(n + " ");
	}

	return kernel;
}

HostInfo SystemInfo::getHostInfo()
{
	HostInfo hostinfo = {"unknown", "unknown"};

	std::string username = runCommand("whoami");
	std::string hostname = runCommand("hostname");

	hostinfo.username = username;
	hostinfo.hostname = hostname;

	return hostinfo;
}
