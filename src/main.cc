#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "libs/json/single_include/nlohmann/json.hpp"
#include "model/AgentReportF/ReportComponent.h"
#include "model/AgentReportF/Builder.h"
using namespace std;
using json = nlohmann::json;
int main() {
    fs::path path = fs::current_path()/"example.json";
    IBuilder* bd = new Builder(path);
    std::cout << "Result compare = "<< MetricParametersConstants::mapOperationCompare[">="](0,5) << std::endl;
    auto firstNodeLevel  = bd->getResult();
    std::cout<<"Agent name : "<<bd->getName()<<'\n';
    std::cout<<"Agent type : "<<bd->getType()<<'\n';
    std::cout<<"Agent interval : "<<bd->getTime()<<'\n';
    std::cout<<"Agent enabled : "<<bd->isEnabled()<<'\n';
    
    for (ReportComposite::Iterator iter(firstNodeLevel); !iter.isEnd(); iter.Next()) {
        auto report_i = (*iter);
        for (auto& point : report_i.first) {
            std::cout << point << std::endl;
        }
        std::cout << "value = "<<report_i.second.getValue() << std::endl;
        std::cout << "critical value = "<< report_i.second.getCriticalValue() << std::endl;
        std::cout << "Result compare = "<< report_i.second.compareIsTrue() << std::endl;
    }
}
