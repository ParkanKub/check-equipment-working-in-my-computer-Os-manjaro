#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>


using namespace std;

long long getDiskRead(){
    ifstream disk("/proc/diskstats");
    string line;
    while(getline(disk,line)){
        istringstream ss(line);
        string name;
        int major, minor;
        long long readIO, readMerges, readSectors , readTime;
        ss >> major >> minor >> name >> readIO >> readMerges >> readSectors >> readTime;
        if (name == "nvme0n1"){
            return readSectors;
        }
    }
    return 0;
}

int main() {
    long long initialRead = getDiskRead();
    this_thread::sleep_for(chrono::seconds(5));
    long long finalRead = getDiskRead();
    long long readSectors = finalRead - initialRead;
    long long readBytes = readSectors * 512;
    double mb = (double)readBytes / (1024 * 1024);
    cout << "Disk Usage: " << mb << " MB/s\n";
}