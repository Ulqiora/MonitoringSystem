#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "libs/json/single_include/nlohmann/json.hpp"
// #include "AgentReportF/ReportComponent.h"

using namespace std;
using json = nlohmann::json;
int main() {
    std::ifstream f("example.json");
    json data = json::parse(f);
    std::cout<<data["enabled"];
    // ReportComposite* firstNodeLevel = new ReportComposite("1Node", nullptr);
    // ReportComposite* SecondNodeLevel = new ReportComposite("2Node", firstNodeLevel);
    // SecondNodeLevel->add(new ReportValue("1Value", 59, SecondNodeLevel));
    // firstNodeLevel->add(SecondNodeLevel);
    // firstNodeLevel->add(new ReportValue("2Value", 8096, firstNodeLevel));
    // firstNodeLevel->add(new ReportValue("3Value", 59, firstNodeLevel));
    // for (ReportComposite::Iterator iter(firstNodeLevel); !iter.isEnd(); iter.Next()) {
    //     auto report_i = (*iter);
    //     for (auto& point : report_i.first) {
    //         std::cout << point << std::endl;
    //     }
    //     std::cout << report_i.second << std::endl;
    // }
}
