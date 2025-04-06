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
#include <array>
#include <cstdio>
#include <sstream>

struct CPUInfo {
	std::string model_name;
	unsigned int processors;
};

struct Time {
	unsigned int hours;
	unsigned int minutes;
};

struct RAMInfo {
	unsigned int total;
	unsigned int used;
	unsigned int percentage;
};

struct HostInfo{
	std::string username;
	std::string hostname;
};

class SystemInfo
{
private:
	static std::string runCommand(const char*);
	static std::vector<std::string> split (const std::string &s, char delim);

public:
	static CPUInfo getCPUInfo();
	static RAMInfo getRAMInfo();
	static std::string getGPU();
	static Time getUptime();
	static std::string getShell();
	static std::string getDistro();
	static std::string getKernel();
	static HostInfo getHostInfo();
};

#endif /* SYSTEMINFO_H */
