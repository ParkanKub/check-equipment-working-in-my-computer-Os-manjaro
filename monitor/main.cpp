#include "cpu/cpu.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>

#include <iostream>
using namespace std;


vector<string> getNumberOfCPUs()
{
    return getCPUName();
}

int main(int argc, char *argv[])
{
    vector<string> numberOfCPUs = getNumberOfCPUs();

    QApplication app(argc, argv);

    QWidget window;
    for (const auto& cpuName : numberOfCPUs)
    {
        long long total = getCPUTotal(cpuName);
        long long idle = getCPUIdle(cpuName);
        double usage = 100.0 * (total - idle) / total;

        QLabel *label = new QLabel("CPU: " + QString::fromStdString(cpuName) + " Usage: " + QString::number(usage, 'f', 2) + "%");
        label->setParent(&window);
        label->move(10, 30 * (&cpuName - &numberOfCPUs[0]));
    }
    window.resize(500, 300);
    window.show();
    return app.exec();
}
