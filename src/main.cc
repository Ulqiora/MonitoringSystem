#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "libs/json/single_include/nlohmann/json.hpp"
#include "AgentReportF/ReportComponent.h"
#include "AgentReportF/Builder.h"
using namespace std;
using json = nlohmann::json;
int main() {
    std::ifstream f("example.json");
    json data = json::parse(f);
    Builder bd;
    bd.byJson(data);
    std::cout<<data["metrics"].is_array();
    // for(auto& it:data.items()){
    //     if(it.value().is_structured()){
    //         std::cout << "Is structured\n";
    //     }
    //     std::cout << it.key() << " : " << it.value() << "\n";
    //     if(!it.value().is_primitive())
    //         for (auto& it1 : it.value().items()) {
    //             if (it1.value().is_structured()) std::cout << "Is object\n";
    //             std::cout << it1.key() << " : " << it1.value() << "\n";
    //         }
    // }
    // std::cout<<data["enabled"];
    // ReportComposite* firstNodeLevel = new ReportComposite("1Node", nullptr);
    // ReportComposite* SecondNodeLevel = new ReportComposite("2Node", firstNodeLevel);
    // SecondNodeLevel->add(new ReportValue("1Value", MetricParameters{"\">=\"",100,59}, SecondNodeLevel));
    // firstNodeLevel->add(SecondNodeLevel);
    // firstNodeLevel->add(new ReportValue("2Value", MetricParameters{"\">=\"",100,59}, firstNodeLevel));
    // firstNodeLevel->add(new ReportValue("3Value", MetricParameters{"\">=\"",100,59}, firstNodeLevel));
    // for (ReportComposite::Iterator iter(firstNodeLevel); !iter.isEnd(); iter.Next()) {
    //     auto report_i = (*iter);
    //     for (auto& point : report_i.first) {
    //         std::cout << point << std::endl;
    //     }
    //     std::cout << report_i.second.getValue() << std::endl;
    // }
}
