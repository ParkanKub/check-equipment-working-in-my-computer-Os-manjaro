#include "cpu/cpu.h"
#include <QApplication>
#include <QMessageBox>
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

    QApplication a(argc, argv);
    QMessageBox msgBox;

    msgBox.setText("Number of CPUs: " + QString::number(numberOfCPUs));
    msgBox.exec();

    QWidget window;
    window.resize(500, 300);
    window.show();
    return a.exec();
}
