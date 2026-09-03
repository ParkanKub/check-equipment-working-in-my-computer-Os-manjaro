#include "cpu/cpu.h"
#include <QApplication>
#include <QWidget>

#include <iostream>
using namespace std;

long long getNumberOfCPUs()
{
    return getCPUName().size();
}

int main(int argc, char *argv[])
{
    long long numberOfCPUs = getNumberOfCPUs();

    cout << "Number of CPUs: " << numberOfCPUs << endl;
    QApplication a(argc, argv);
    QWidget window;
    window.resize(500, 300);
    window.show();
    return a.exec();
}
