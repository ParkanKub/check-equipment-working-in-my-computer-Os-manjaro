#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ifstream ram("/proc/meminfo");
    string line;
    long long memTotal = 0;
    long long memAvailable = 0;
    while(getline(ram,line)){
        istringstream ss(line);
        string name;
        long long value;
        ss >> name >> value;
        if(name == "MemTotal:")
            memTotal = value;
        
        if(name == "MemAvailable:")
            memAvailable = value;
        
    }
    long long memUsed = memTotal - memAvailable;

    double ramPercent =
    (double)memUsed / memTotal * 100;

    cout << "RAM Usage: " << ramPercent << "%\n";
}
