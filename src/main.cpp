#include <iostream>
#include <thread>
#include "model/AgentReportF/ReportComponent.h"
#include <vector>
using namespace std;

int main() {
    ReportComposite* firstNodeLevel = new ReportComposite("Root",nullptr);
    ReportComposite* SecondNodeLevel = new ReportComposite("Root1",firstNodeLevel);
    firstNodeLevel->add(SecondNodeLevel);
    firstNodeLevel->add(new ReportValue("RAM",8096,firstNodeLevel));
    SecondNodeLevel->add(new ReportValue("Processor state",59,SecondNodeLevel));
    firstNodeLevel->add(new ReportValue("KUKU",59,firstNodeLevel));
    ReportComposite::Iterator iter(firstNodeLevel);
    iter.Next();
    auto report_i = *(iter);
    for(auto& point:report_i.first){
        std::cout<<point<<std::endl;
    }
    std::cout<<report_i.second<<std::endl;
}
