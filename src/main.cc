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
#include "model/Agents/Memory/MemoryAgent.h"
#include "model/Agents/Network/NetworkAgent.h"
// using json = nlohmann::json;
int main() {
    fs::path path = fs::current_path()/"logs"/"NetworkAgent.json";
    IBuilder* bd = new Builder(path);
    IAgent* agent = new NetworkAgent(bd);
    agent->SetUrl("help.iwantmyname.com");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    agent->update();
    std::cout<<agent->toStdString()<<'\n';
    agent->SetUrl("help.iwantmynae.com");
    agent->update();
    std::cout<<agent->toStdString()<<'\n';

    // std::string command = "ping -c 1 " "help.iwantmyname.com"  " >/dev/null";
    // std::string output = "";
    // char buffer[128] = "";
    // FILE* pipe = popen(command.c_str(), "r");
    // if (!pipe) {
    //     throw std::runtime_error("popen() failed!");
    // }
    // if (std::feof(pipe)) {
    //     // return;
    // }
    // while (!std::feof(pipe)) {
    //     if (std::fgets(buffer, 128, pipe) != NULL)
    //         output += buffer;
    // }
    // pclose(pipe);
    // char* point;
    // double value = strtod(buffer,&point);
    // std::cout<<value;
    // std::string command = "ping -c 1 help.iwantmyname.com ";
    
    // // Выполняем команду в дочернем процессе и открываем канал для чтения вывода
    // FILE* pipe = popen(command.c_str(), "r");
    // if (!pipe) {
    //     std::cerr << "Ошибка выполнения команды";
    //     return 1;
    // }
    
    // // Читаем вывод команды построчно и сохраняем его в переменную output
    // std::array<char, 128> buffer;
    // std::string output;
    // while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    //     output += buffer.data();
    // }
    
    // // Закрываем канал и выводим полученный вывод команды
    // pclose(pipe);
    // std::cout << output;
    
    // return 0;
}
