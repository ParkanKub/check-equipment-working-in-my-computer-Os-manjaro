#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

vector<string> getData()
{
    ifstream cpuData("/proc/stat");
    string line;
    getline(cpuData, line);
    return {line};
}
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
        if(cpu.rfind("cpu",0) == 0){
            cpuNames.push_back(cpu);
        }

    }
    return cpuNames;
}

long long getCPUIdle()
{
    vector<string> data = getData();
    istringstream ss(data[0]);

    string cpu;
    long long user, nice, system, idle;

    ss >> cpu >> user >> nice >> system >> idle;
    return idle;
}
long long getCPUTotal()
{
    vector<string> data = getData();
    istringstream ss(data[0]);
    string cpu;
    long long user, nice, system, idle;
    ss >> cpu >> user >> nice >> system >> idle;

    return user + nice + system + idle;
}

int main()
{
vector<string> cpu = getCPUName();
for (string cpuName : cpu){
    
    cout << cpuName << "\n";
}
    return 0;

    // long long idle1 = getCPUIdle();
    // long long total1 = getCPUTotal();
    // this_thread::sleep_for(chrono::seconds(1));

    // long long idle2 = getCPUIdle();
    // long long total2 = getCPUTotal();

    // long long idle = idle2 - idle1;
    // long long total = total2 - total1;
    // double cpu_usage = 100.0 * (total - idle) / total;
    // cout << "CPU Usage:" << cpu_usage << "%" << endl;
}
