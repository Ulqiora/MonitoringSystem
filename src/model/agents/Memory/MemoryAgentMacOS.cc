#include <mach/mach.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#include "../../AgentReportF/Builder.h"
#include "MemoryAgent.h"

MemoryAgent::MemoryAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    info_ = bd->getAgentInfo();
    report_ = bd->getResult();
    update();
}

void MemoryAgent::update() {
    iter_.First();
    setRamTotal();
    setRamPercent();
    setHardVolume();
    setHardOps();
    setHardThroughput();
}

void MemoryAgent::setRamTotal() {
    int mib[2] = {CTL_HW, HW_MEMSIZE};
    int64_t physical_memory;
    size_t length = sizeof(int64_t);
    if (sysctl(mib, 2, &physical_memory, &length, NULL, 0) < 0) {
        std::cerr << "Error: sysctl call failed";
        return;
    }
    (*iter_).second.setValue(physical_memory / (1024.0 * 1024.0)), iter_.Next();
}

void MemoryAgent::setRamPercent() {
    char command[]="echo \"scale=2; ($(/usr/bin/vm_stat | grep \"Pages active\" | awk \'{print $3}\' | sed 's/\\.//') "
        "+ $(/usr/bin/vm_stat | grep \"Pages wired down\" | awk '{print $4}' | sed 's/\\.//')) / "
        "$(/usr/sbin/sysctl -n hw.memsize | awk '{print $1/4096}' | sed 's/\\..*//') * 100\" | bc";
    FILE* file = popen(command, "r");
    if (!file) throw std::runtime_error("popen() failed!");
    char buffer[128];
    char* u;
    std::fgets(buffer, 128, file);
    (*iter_).second.setValue(strtod(buffer + 0, &u)), iter_.Next();
    pclose(file);
}

void MemoryAgent::setHardVolume() {
    char command[]="df -m / | awk 'NR==2{print $3}'";
    FILE* file = popen(command, "r");
    if (!file) throw std::runtime_error("popen() failed!");
    char buffer[128];
    char* u;
    std::fgets(buffer, 128, file);
    (*iter_).second.setValue(strtod(buffer + 0, &u)/1024.0), iter_.Next();
    pclose(file);
}

void MemoryAgent::setHardOps() {
    char command[]="iostat -d disk0 | awk 'NR==3{print $2}'";
    FILE* file = popen(command, "r");
    if (!file) throw std::runtime_error("popen() failed!");
    char buffer[128];
    char* u;
    std::fgets(buffer, 128, file);
    (*iter_).second.setValue(strtod(buffer + 0, &u)), iter_.Next();
    pclose(file);
}

void MemoryAgent::setHardThroughput() {
    struct statfs fs_info;
    if (statfs("/", &fs_info) != 0) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return;
    }
    double disk_size =
        static_cast<double>(fs_info.f_bsize * fs_info.f_blocks) / (1024 * 1024 * 1024);  // размер диска в Гб
    double free_space = static_cast<double>(fs_info.f_bsize * fs_info.f_bfree) /
                        (1024 * 1024 * 1024);                     // свободное место в Гб
    double used_space = disk_size - free_space;                   // занятое место в Гб
    double io_time = 1.0 / (fs_info.f_iosize / 1000.0 / 1000.0);  // время на I/O операции в секундах
    double max_throughput = used_space / io_time;  // максимальная пропускная способность в Гб/с
    (*iter_).second.setValue(max_throughput), iter_.Next();
}

ReportComposite::Iterator MemoryAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& MemoryAgent::GetInfoAboutAgent() { return info_; }

std::string MemoryAgent::toStdString() {
    std::stringstream ss;
    auto time = std::chrono::system_clock::now();
    std::time_t time_s = std::chrono::system_clock::to_time_t(time);
    ss<<std::put_time(localtime(&time_s),"%Y:%m:%d, %a.   ");
    ss<<info_.name_<<" : ";
    ReportComposite::Iterator iter(iter_);
    for (iter.First(); !iter.isEnd(); iter.Next()) {
        for (auto str_v : (*iter).first) ss << str_v << ' ';
        ss << "=" << std::setw(10) << std::left << (*iter).second.getValue()<<"; ";
    }
    return ss.str();
}

bool MemoryAgent::SetUrl(std::string_view) { return false; }