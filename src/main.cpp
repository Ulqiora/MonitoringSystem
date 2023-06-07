#include <iostream>
#include <thread>
#include "ReportComponent.h"
#include <vector>
using namespace std;

int main() {
    ReportComponent* report = new ReportComposite();
    report->add(new ReportValue("Processor state",59));
    report->add(new ReportValue("RAM",8096));
}
