#include "cpu/cpu.h"
#include <iostream>
using namespace std;

long long getNumberOfCPUs()
{
    return getCPUName().size();
}

int main()
{
    long long numberOfCPUs = getNumberOfCPUs();

    cout << "Number of CPUs: " << numberOfCPUs << endl;
}