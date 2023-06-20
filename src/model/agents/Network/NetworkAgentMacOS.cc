#include "NetworkAgent.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "../../AgentReportF/Builder.h"

NetworkAgent::NetworkAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    iter_.First();
    update();
}

void NetworkAgent::update() {
    iter_.First();
    checkUrl();
    getSpeedNetInterface();
}
void NetworkAgent::getSpeedNetInterface() {
    std::string cmd = "netstat -I en0";
    FILE* stream = popen(cmd.c_str(), "r");
    if (stream) {
        const int max_line = 255;
        char buffer[max_line];
        int ibytes1, opkts1;
        while (!feof(stream)) {
            if (fgets(buffer, max_line, stream) != NULL) {
                if (sscanf(buffer, "%s %d %*d %*d %*d %d %*d %*d %*d", buffer, &ibytes1, &opkts1) == 3) {
                    break;
                }
            }
        }
        pclose(stream);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        stream = popen(cmd.c_str(), "r");
        if (stream) {
            int ibytes2, opkts2;
            while (!feof(stream)) {
                if (fgets(buffer, max_line, stream) != NULL) {
                    if (sscanf(buffer, "%s %d %*d %*d %*d %d %*d %*d %*d", buffer, &ibytes2, &opkts2) == 3) {
                        break;
                    }
                }
            }
            pclose(stream);
            (*iter_).second.setValue(fabs(((double)ibytes2 - ibytes1)/(1024.0*1024.0)));
        } else {
            std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
        exit(1);
    }
    iter_.Next();
}

[[nodiscard]] bool NetworkAgent::SetUrl(std::string_view url) {
    URL_ = url;
    return true;
}

[[nodiscard]] ReportComposite::Iterator NetworkAgent::GetReport() {
    return ReportComposite::Iterator(iter_);
}

[[nodiscard]] const InfoAgent& NetworkAgent::GetInfoAboutAgent() { return info_; }

[[nodiscard]] std::string NetworkAgent::toStdString() {
    std::stringstream ss;
    auto time = std::chrono::system_clock::now();
    std::time_t time_s = std::chrono::system_clock::to_time_t(time);
    ss<<std::put_time(localtime(&time_s),"%Y:%m:%d, %a.   ");
    ss<<info_.name_<<" : ";
    ReportComposite::Iterator iter(iter_);
    for (iter.First(); !iter.isEnd(); iter.Next()) {
        for (auto str_v : (*iter).first) {
            if (str_v == "URL") {
                ss << URL_ << ' ';
            } else {
                ss << str_v << ' ';
            }
        }
        ss << "=" << std::setw(10) << std::left << (*iter).second.getValue()<<"; ";
    }
    return ss.str();
}

void NetworkAgent::checkUrl() {
    // if(URL_.empty()) return ;
    // std::string command = "curl -I " + URL_ + " -o /dev/null -s -w '%{http_code}\n'";
    // std::string output = "";
    // char buffer[128];
    // std::FILE* pipe = popen(command.c_str(), "r");
    // if (!pipe) {
    //     throw std::runtime_error("popen() failed!");
    // }
    // while (!std::feof(pipe)) {
    //     if (std::fgets(buffer, 128, pipe) != NULL) output += buffer;
    // }
    // pclose(pipe);
    if (URL_.empty()) {
        iter_.Next();
        return;
    }
    std::string command = "ping -c 1 " + URL_ + " | awk 'NR==5{print $7}'";
    std::string output = "";
    char buffer[128] = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    if (std::feof(pipe)) {
        (*iter_).second.setValue(0.0), iter_.Next();
        return;
    }
    while (!std::feof(pipe)) {
        if (std::fgets(buffer, 128, pipe) != NULL)
            output += buffer;
    }
    pclose(pipe);
    char* point;
    double value = strtod(buffer,&point);
    if ((buffer + 0) != point) {
        (*iter_).second.setValue((buffer != point && value == 0.0) ? 1.0 : 0.0), iter_.Next();
    } else {
        (*iter_).second.setValue(0.0), iter_.Next();
    }
}
