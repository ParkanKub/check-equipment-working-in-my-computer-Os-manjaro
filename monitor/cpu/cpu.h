#pragma once

#include <vector>
#include <string>

std::vector<std::string> getCPUName();
long long getCPUIdle(std::string cpuName);
long long getCPUTotal(std::string cpuName);
