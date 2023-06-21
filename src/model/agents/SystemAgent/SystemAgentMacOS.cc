#include "SystemAgent.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "../../AgentReportF/Builder.h"

SystemAgent::SystemAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {}

void SystemAgent::update(){

}
std::string SystemAgent::toStdString(){
    
}
bool SystemAgent::SetUrl(std::string_view sv){
    return false;
}
const InfoAgent& SystemAgent::GetInfoAboutAgent(){
    return info_;
}
ReportComposite::Iterator SystemAgent::GetReport(){
    return ReportComposite::Iterator(iter_);
}
