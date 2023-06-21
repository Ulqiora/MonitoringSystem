#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "../../AgentReportF/Builder.h"
#include "SystemAgent.h"

SystemAgent::SystemAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {}

void SystemAgent::update() {
    iter_.First();
    setPrivileges();
    setTotalSwap();
    setUsedSwap();
    setProcQueuelength();
    setVirtualMemVolume();
    setVirtualMemFree();
    setInodes();
    setHardReadTime();
    setSystemErrors();
    setUserAuths();
}

std::string SystemAgent::toStdString() {
    iter_.First();
    std::stringstream ss;
    auto time = std::chrono::system_clock::now();
    std::time_t time_s = std::chrono::system_clock::to_time_t(time);
    ss << std::put_time(localtime(&time_s), "%Y:%m:%d, %a.   ");
    ss << info_.name_ << " : ";
    ReportComposite::Iterator iter(iter_);
    for (iter.First(); !iter.isEnd(); iter.Next()) {
        for (auto str_v : (*iter).first) ss << str_v << ' ';
        ss << "=" << std::setw(10) << std::left << (*iter).second.getValue() << "; ";
    }
    return ss.str();
}

bool SystemAgent::SetUrl(std::string_view sv) { return false; }

const InfoAgent& SystemAgent::GetInfoAboutAgent() { return info_; }

ReportComposite::Iterator SystemAgent::GetReport() { return ReportComposite::Iterator(iter_); }

void SystemAgent::setPrivileges() {
    std::string cmd = "iostat | awk '{print $9}' | tail -n +3";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int percent = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &percent);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(percent),iter_.Next();
    cmd = "iostat | awk '{print $8}' | tail -n +3";
    stream = popen(cmd.c_str(), "r");
    buffer[0]='\0', percent = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &percent);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(percent),iter_.Next();
    cmd = "iostat | awk '{print $7}' | tail -n +3";
    stream = popen(cmd.c_str(), "r");
    buffer[0]='\0', percent = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &percent);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(percent),iter_.Next();
}

void SystemAgent::setTotalSwap() {
    std::string cmd = "sysctl vm.swapusage | awk '{print $4}' | sed 's/.$//'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}

void SystemAgent::setUsedSwap() {
    std::string cmd = "sysctl vm.swapusage | awk '{print $7}' | sed 's/.$//'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}

void SystemAgent::setProcQueuelength() {
    std::string cmd = "ps -e -o stat | tail -n +2 | grep S | wc -l | awk '$1=$1'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}
void SystemAgent::setVirtualMemVolume() {
    std::string cmd = "sysctl vm.swapusage | awk '{print $4}' | sed 's/.$//'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}
void SystemAgent::setVirtualMemFree() {
    std::string cmd = "sysctl vm.swapusage | awk '{print $10}' | sed 's/.$//'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}
void SystemAgent::setInodes() {
    std::string cmd = "df / | awk '{print $6}' | tail -n +2 | sed 's/.$//'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}
void SystemAgent::setHardReadTime() {
    (*iter_).second.setValue(0.0),iter_.Next();
}
void SystemAgent::setSystemErrors() {
    std::string cmd = "cat /var/log/fusioninventory.log | grep error | wc -l | awk '$1=$1'";
    FILE* stream = popen(cmd.c_str(), "r");
    const int max_line = 255;
    char buffer[max_line];
    int total = 0;
    if (stream) {
        if (!feof(stream) && fgets(buffer, max_line, stream) != NULL) sscanf(buffer, "%d", &total);
        pclose(stream);
    } else {
        std::cerr << "Ошибка выполнения команды " << cmd << std::endl;
    }
    (*iter_).second.setValue(total),iter_.Next();
}
void SystemAgent::setUserAuths() {
    (*iter_).second.setValue(0.0),iter_.Next();
}