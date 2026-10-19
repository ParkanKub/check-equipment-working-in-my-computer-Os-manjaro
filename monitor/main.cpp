#include "cpu/cpu.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

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
    QLabel cpuLabel("CPU: Loading...");
    QVBoxLayout layout(&window);
    layout.addWidget(&cpuLabel);

    for (const auto& cpuName : numberOfCPUs)
    {
        long long total = getCPUTotal(cpuName);
        long long idle = getCPUIdle(cpuName);
        double usage = 100.0 * (total - idle) / total;

        QLabel *label = new QLabel("CPU: " + QString::fromStdString(cpuName) + " Usage: " + QString::number(usage, 'f', 2) + "%");
        layout.addWidget(label);
    }
    window.resize(500, 300);
    window.show();
    return app.exec();
}
