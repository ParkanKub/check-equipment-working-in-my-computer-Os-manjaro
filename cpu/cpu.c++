#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

long long getCPUIdle(){
    ifstream cpuinto("/proc/stat");
    string line;
    getline(cpuinto,line);
    istringstream ss(line);
     string cpu;
     long long user,nice,system,idle;
     ss >> cpu >> user >> nice >> system >> idle;
     return idle;
}
long long getCPUTotal(){
    ifstream cpuinto("/proc/stat");
    string line;
    getline(cpuinto,line);
    istringstream ss(line);
     string cpu;
     long long user,nice,system,idle;
     ss >> cpu >> user >> nice >> system >> idle;
     return user + nice + system + idle;
}


int main (){

    long long idle1 = getCPUIdle();
    long long total1 = getCPUTotal();
    this_thread::sleep_for(chrono::seconds(1));

    long long idle2 = getCPUIdle();
    long long total2 = getCPUTotal();

    long long idle = idle2 - idle1;
    long long total = total2 - total1;
    double cpu_usage = 100.0* (total - idle) /total;
    cout << "CPU Usage:" << cpu_usage << "%" << endl;
return 0;
}
