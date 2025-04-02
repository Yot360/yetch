#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>
#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <algorithm>

class SystemInfo
{
public:
	static std::string getCPUName();
	static std::string getTotalRAM();
};

#endif /* SYSTEMINFO_H */
