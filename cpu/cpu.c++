#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

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
        if (cpu.rfind("cpu", 0) == 0)
        {
            cpuNames.push_back(cpu);
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
        long long user, nice, system, idle;
        ss >> cpu >> user >> nice >> system >> idle;
        if (cpu == cpuName)
        {
            return idle;
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
        long long user, nice, system, idle;
        ss >> cpu >> user >> nice >> system >> idle;
        if (cpu == cpuName)
        {

            return user + nice + system + idle;
        }
    }
    return -1;
}

int main()
{
    vector<string> cpu = getCPUName();
    for (string cpuName : cpu)
    {

        long long idle1 = getCPUIdle(cpuName);
        long long total1 = getCPUTotal(cpuName);
        this_thread::sleep_for(chrono::seconds(1));

        long long idle2 = getCPUIdle(cpuName);
        long long total2 = getCPUTotal(cpuName);

        long long idle = idle2 - idle1;
        long long total = total2 - total1;
        double cpu_usage = 100.0 * (total - idle) / total;

        cout << cpuName << " " << cpu_usage << "%"<< "\n";
    }
    return 0;
}
