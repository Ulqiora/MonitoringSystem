// #include <fstream>
// #include <iostream>
// #include <string>
#include <thread>
// #include <vector>
// #include <thread>
// #include <filesystem>
// #include <sys/vfs.h>
#include "libs/json/single_include/nlohmann/json.hpp"
#include "model/AgentReportF/Builder.h"
#include "model/AgentReportF/ReportComponent.h"
#include "model/Agents/CPU/CpuAgent.h"
#include "model/KernelLoader/KernelLoader.h"
// #include "model/Agents/Memory/MemoryAgent.h"
using namespace std;
// using json = nlohmann::json;
int main() {
    KernelLoader kl;
    kl.start();
    fs::path path = fs::current_path()/"example.json";
    IBuilder* bd = new Builder(path);
    IAgent* agent=new CpuAgent(bd);
    std::cout<<agent->toStdString()<<'\n';
    std::this_thread::sleep_for(1s);
    agent->update();
    std::cout<<agent->toStdString()<<'\n';
}