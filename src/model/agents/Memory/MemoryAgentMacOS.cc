#include <mach/mach.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <cstdio>

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
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count) != KERN_SUCCESS) {
        std::cerr << "Error: task_info failed ";
        return;
    }
    const int64_t used_phys_mem = (int64_t)t_info.resident_size;
    int mib[2] = {CTL_HW,HW_MEMSIZE};
    int64_t total_phys_mem;
    size_t length = sizeof(total_phys_mem);
    if (sysctl(mib, 2, &total_phys_mem, &length, NULL, 0) < 0) {
        std::cerr << "Error: sysctl call failed";
        return;
    }
    (*iter_).second.setValue((float)used_phys_mem / (float)total_phys_mem * 100.0), iter_.Next();
}

void MemoryAgent::setHardVolume(){
    struct statfs diskInfo;
    unsigned long long freeSpace, totalSpace;
    if (statfs("/", &diskInfo) == 0) {
        freeSpace = (unsigned long long) diskInfo.f_bsize * (unsigned long long) diskInfo.f_bfree;
        totalSpace = (unsigned long long) diskInfo.f_bsize * (unsigned long long) diskInfo.f_blocks;
        (*iter_).second.setValue(((float)totalSpace-freeSpace)/(float)totalSpace*100.0), iter_.Next();
    } else {
        std::cerr << "Failed to retrieve file system information" << std::endl;
    }
}

void MemoryAgent::setHardOps(){
    struct statfs fs_info;
    if (statfs("/", &fs_info) != 0) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return ;
    }
    (*iter_).second.setValue(fs_info.f_iosize / fs_info.f_bsize), iter_.Next();
}

void MemoryAgent::setHardThroughput(){
    struct statfs fs_info;
    if (statfs("/", &fs_info) != 0) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return;
    }
    double disk_size = static_cast<double>(fs_info.f_bsize * fs_info.f_blocks) / (1024 * 1024 * 1024); // размер диска в Гб
    double free_space = static_cast<double>(fs_info.f_bsize * fs_info.f_bfree) / (1024 * 1024 * 1024); // свободное место в Гб
    double used_space = disk_size - free_space; // занятое место в Гб
    double io_time = 1.0 / (fs_info.f_iosize / 1000.0 / 1000.0); // время на I/O операции в секундах
    double max_throughput = used_space / io_time; // максимальная пропускная способность в Гб/с
    (*iter_).second.setValue(max_throughput), iter_.Next();
}

ReportComposite::Iterator MemoryAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& MemoryAgent::GetInfoAboutAgent() { return info_; }