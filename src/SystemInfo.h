#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>
#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <algorithm>
#include <memory>
#include <array>
#include <vector>

struct CPUInfo {
	std::string model_name;
	unsigned int processors;
};

struct Time {
	unsigned int hours;
	unsigned int minutes;
};

class SystemInfo
{
private:
	static std::string runCommand(const char*);
	static std::vector<std::string> split (const std::string &s, char delim);

public:
	static CPUInfo getCPUInfo();
	static std::string getTotalRAM();
	static std::string getGPU();
	static Time getUptime();
};

#endif /* SYSTEMINFO_H */
