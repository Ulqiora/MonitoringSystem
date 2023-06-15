#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "libs/json/single_include/nlohmann/json.hpp"
#include "model/AgentReportF/ReportComponent.h"
#include "model/AgentReportF/Builder.h"
#include "model/Agents/CPU/CpuAgent.h"
using namespace std;
using json = nlohmann::json;
int main() {
    fs::path path = fs::current_path()/"example.json";
    IBuilder* bd = new Builder(path);
    IAgent* agent=new CpuAgent(bd);
    agent->update();
    agent->update();
    for (ReportComposite::Iterator iter(agent->GetReport()); !iter.isEnd(); iter.Next()) {
        auto report_i = (*iter);
        for (auto& point : report_i.first) {
            std::cout << point << std::endl;
        }
        std::cout << "value = "<<report_i.second.getValue() << std::endl;
        std::cout << "critical value = "<< report_i.second.getCriticalValue() << std::endl;
        std::cout << "Result compare = "<< report_i.second.compareIsTrue() << std::endl;
    }


    // auto firstNodeLevel  = bd->getResult();
    // std::cout<<"Agent name : "<<bd->getAgentInfo().name_<<'\n';
    // std::cout<<"Agent type : "<<bd->getAgentInfo().typeAgent_<<'\n';
    // std::cout<<"Agent interval : "<<bd->getAgentInfo().time_seconds_<<'\n';
    // std::cout<<"Agent enabled : "<<bd->getAgentInfo().enabled_<<'\n';
    // for (ReportComposite::Iterator iter(firstNodeLevel); !iter.isEnd(); iter.Next()) {
    //     auto report_i = (*iter);
    //     for (auto& point : report_i.first) {
    //         std::cout << point << std::endl;
    //     }
    //     std::cout << "value = "<<report_i.second.getValue() << std::endl;
    //     std::cout << "critical value = "<< report_i.second.getCriticalValue() << std::endl;
    //     std::cout << "Result compare = "<< report_i.second.compareIsTrue() << std::endl;
    // }
}
