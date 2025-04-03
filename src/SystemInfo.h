#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>
#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <algorithm>
#include <memory>
#include <array>

struct CPUInfo {
	std::string model_name;
	unsigned int processors;
};

class SystemInfo
{
public:
	static CPUInfo getCPUInfo();
	static std::string getTotalRAM();
	static std::string getGPU();
};

#endif /* SYSTEMINFO_H */
