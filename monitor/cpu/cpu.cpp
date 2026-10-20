#include "cpu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

vector<string> getCPUName() 
{
    ifstream cpuData("/proc/stat");
    string line;
    vector<string> cpuNames;
    while (getline(cpuData, line))
    {
        istringstream ss(line);
        string cpu;
        ss >> cpu;
        if(cpu == "cpu" || cpu.find("cpu") == 0 && cpu.size() > 3) 
        {
            cpuNames.push_back(cpu);//ติดไว้ก่อน
        }
    }
    return cpuNames;
}

long long getCPUIdle(string cpuName)
{
    ifstream cpuIdle("/proc/stat");
    string line;

    while (getline(cpuIdle, line))
    {
        istringstream ss(line);

        string cpu;

        if(!(ss>>cpu)) continue; // Skip lines that don't start with a CPU name

        if (cpu == cpuName)
        {
        long long value;
        long long idle = 0;
        long long iowait = 0;
        if(!(ss >> value >> value >> value >> idle)) return -1; // Skip lines that don't have enough values
        ss >> iowait; // Read the iowait value
        return idle + iowait;
    }
    }
    return -1;
}
long long getCPUTotal(string cpuName)

{
    ifstream cpuTotal("/proc/stat");
    string line;
    while (getline(cpuTotal, line))
    {
        istringstream ss(line);
        string cpu;
        if(!(ss>>cpu))continue; // Skip lines that don't start with a CPU name

        if (cpu == cpuName)
        {
            long long value;
            long long total =0;
            while (ss >> value){
                total += value;
            }
            return total;
        }
    }
    return -1;
}