#include "cpu/cpu.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
// #include <QDebug>

#include <vector>
#include <string>
#include <map>

#include <iostream>
using namespace std;

struct CPUReading
{
    long long total;
    long long idle;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    vector<string> cpuNames = getCPUName();

    QWidget window;
    window.setWindowTitle("System Monitor");
    QVBoxLayout *layout = new QVBoxLayout(&window);
    vector<QLabel *> cpuLabels;

    for (const auto &cpuName : cpuNames)
    {
        QLabel *label = new QLabel(QString::fromStdString(cpuName) + ": Loading...");
        layout->addWidget(label);
        cpuLabels.push_back(label);
    }
    map<string, CPUReading> previous;
    for (const auto &cpuName : cpuNames)
    {
        previous[cpuName] = {
            getCPUTotal(cpuName),
            getCPUIdle(cpuName)};
    }

    QTimer *timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]()
                     {
        for (size_t i = 0; i < cpuNames.size(); ++i)
    {
    const string& cpuName = cpuNames[i];

    long long total = getCPUTotal(cpuName);
    long long idle = getCPUIdle(cpuName);
    CPUReading old = previous[cpuName];

    if (total < 0 || idle <0 || old.total <0||old.idle <0){
        cpuLabels[i]->setText(
            QString::fromStdString(cpuName) + 
            ": Read error"
        );
        previous[cpuName] = {total, idle};
        continue;
    }
    long long deltaTotal = total - old.total;
    long long deltaIdle = idle - old.idle;

    if(deltaTotal == 0){
        double usage = 100.0 * (deltaTotal - deltaIdle) / deltaTotal;

        if(usage < 0.0) usage = 0.0;
        if(usage > 100.0) usage = 100.0;

        cpuLabels[i]->setText(
            QString::fromStdString(cpuName) + 
            ": " + QString::number(usage, 'f', 2) + "%"
        );
    }
    previous[cpuName] = {total, idle};
        
    } 
});
    timer->start(500);

    window.resize(500, 300);
    window.show();
    return app.exec();
}
