#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ifstream disk("/proc/diskstats");
    string line;
    long long readSectors = 0;
    long long writeSectors = 0;
    while(getline(disk,line)){
        istringstream ss(line);
        string name;
        long long value;
    }

}