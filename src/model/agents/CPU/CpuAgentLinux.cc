#include <fstream>

#include <unistd.h>
#include "../../AgentReportF/Builder.h"
#include "CpuAgent.h"

CpuAgent::CpuAgent(IBuilder* bd) : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    update();
}

void CpuAgent::getCpuLoaded() {
    std::ifstream stat_stream("/proc/stat");
    std::string line;
    std::getline(stat_stream, line);
    long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    std::sscanf(line.c_str(), "cpu %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle,
                &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    long total_time = user + nice + system + idle + iowait + irq + softirq + steal;
    long idle_time = idle + iowait;
    (*iter_).second.setValue(1.0 - (double)idle_time / total_time), iter_.Next();
    stat_stream.close();
}

void CpuAgent::getNumProc() { (*iter_).second.setValue(sysconf(_SC_NPROCESSORS_ONLN)), iter_.Next(); }

void CpuAgent::update() {
    iter_.First();
    getCpuLoaded();
    getNumProc();
}

ReportComposite::Iterator CpuAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& CpuAgent::GetInfoAboutAgent() { return info_; }