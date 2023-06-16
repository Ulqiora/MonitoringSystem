#include "MemoryAgent.h"
#include "../../AgentReportF/Builder.h"
#include <sys/sysinfo.h>
#include <sys/statvfs.h>


MemoryAgent::MemoryAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    update();
}

void MemoryAgent::update() {
    iter_.First();
    setRamTotal();
    setRamPercent();
}

void MemoryAgent::setRamTotal() {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        (*iter_).second.setValue(si.totalram / 1024 / 1024), iter_.Next();
        // cout << "Total RAM: " << si.totalram / 1024 / 1024 << " MB" << endl;
    }
}

void MemoryAgent::setRamPercent() {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        double used_mem = si.totalram - si.freeram;
        // double mem_percent = used_mem / si.totalram * 100.0;
        (*iter_).second.setValue(used_mem / si.totalram * 100.0), iter_.Next();
        // cout << "Memory usage: " << mem_percent << "%" << endl;
    }
}

void MemoryAgent::setHardVolume(){
    struct statvfs fiData;
    if (statvfs("/", &fiData) == 0) {
        unsigned long long totalSize = fiData.f_frsize * fiData.f_blocks;
        unsigned long long freeSpace = fiData.f_bfree * fiData.f_frsize;
        (*iter_).second.setValue(100.0 - ((double)fiData.f_bfree / (double)fiData.f_blocks) * 100.0), iter_.Next();
        // cout << "Total disk space: " << totalSize / (1024 * 1024) << " MB" << endl;
        // cout << "Free disk space: " << freeSpace / (1024 * 1024) << " MB" << endl;
        // cout << "Used disk space: " << usedSpacePercent << "%" << endl;
    }
}

void MemoryAgent::setHardOps(){
    FILE *diskstats = fopen("/proc/diskstats", "r");
    char line[1024];
    int major = 0, minor = 0;
    char device[256] = {0};
    unsigned int reads = 0, writes = 0;
    while (fgets(line, sizeof(line), diskstats)) {
        sscanf(line, "%d %d %s %u %*u %u %*u %*u %*u %*u %*u %*u %*u %*u %u", 
        &major, &minor, device, &reads, &writes);
        if (strstr(device, "/dev/") == device) {
            (*iter_).second.setValue(reads + writes), iter_.Next();
            break;
        }
    }
    fclose(diskstats);
}

void MemoryAgent::setHardThroughput(){

}

ReportComposite::Iterator MemoryAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& MemoryAgent::GetInfoAboutAgent() { return info_; }