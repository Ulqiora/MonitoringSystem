#include <iostream>
#include <thread>
#include "model/AgentReportF/ReportComponent.h"
#include <vector>
using namespace std;

int main() {
    ReportComposite* report = new ReportComposite("Root",nullptr);
    report->add(new ReportValue("Processor state",59,report));
    report->add(new ReportValue("RAM",8096,report));
}
