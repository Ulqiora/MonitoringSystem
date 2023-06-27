#include "MemoryAgent.h"
#include "../../AgentReportF/Serializer.h"
#include <sys/sysinfo.h>
#include <sys/statvfs.h>


MemoryAgent::MemoryAgent(ISerializer* bd)
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
    }
}

void MemoryAgent::setRamPercent() {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        double used_mem = si.totalram - si.freeram;
        (*iter_).second.setValue(used_mem / si.totalram * 100.0), iter_.Next();
    }
}

void MemoryAgent::setHardVolume(){
    struct statvfs fiData;
    if (statvfs("/", &fiData) == 0) {
        unsigned long long totalSize = fiData.f_frsize * fiData.f_blocks;
        unsigned long long freeSpace = fiData.f_bfree * fiData.f_frsize;
        (*iter_).second.setValue(100.0 - ((double)fiData.f_bfree / (double)fiData.f_blocks) * 100.0), iter_.Next();
    }
}

void MemoryAgent::setHardOps(){
    std::ifstream diskstats("/proc/diskstats");
    std::string line;
    int maxIO=0;
    std::getline(diskstats, line);
    while (std::getline(diskstats, line)) {
        long long reads, writes;
        sscanf(line.c_str(), "   8   0 %*s %lld %*d %lld", &reads, &writes);
        if(reads+writes>maxIO) maxIO = reads+writes;
        std::cout << "Reads: " << reads << " Writes: " << writes << std::endl;
    }
    diskstats.close();
    (*iter_).second.setValue(maxIO), iter_.Next();
}

void MemoryAgent::setHardThroughput(){
    
}

ReportComposite::Iterator MemoryAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& MemoryAgent::GetInfoAboutAgent() { return info_; }