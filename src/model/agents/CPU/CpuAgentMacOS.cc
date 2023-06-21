#include "CpuAgent.h"

#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "../../AgentReportF/Builder.h"

CpuAgent::CpuAgent(IBuilder* bd) : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    update();
}

void CpuAgent::update() {
    iter_.First();
    double loadAverage[3];
    if (getloadavg(loadAverage, 3) != -1) {
        (*iter_).second.setValue(loadAverage[0]), iter_.Next();
    } else {
        std::cout << "Не удалось получить информацию о загрузке процессора." << std::endl;
    }
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t len;
    sysctl(mib, 4, NULL, &len, NULL, 0);
    (*iter_).second.setValue(len / sizeof(struct kinfo_proc)), iter_.Next();
}

void CpuAgent::getCpuLoaded() {
    double loadAverage[3];
    if (getloadavg(loadAverage, 3) != -1) {
        (*iter_).second.setValue(loadAverage[0]), iter_.Next();
    } else {
        std::cout << "Не удалось получить информацию о загрузке процессора." << std::endl;
    }
}

void CpuAgent::getNumProc() {
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t len;
    sysctl(mib, 4, NULL, &len, NULL, 0);
    (*iter_).second.setValue(len / sizeof(struct kinfo_proc)), iter_.Next();
}

ReportComposite::Iterator CpuAgent::GetReport() { return ReportComposite::Iterator(iter_); }

const InfoAgent& CpuAgent::GetInfoAboutAgent() { return info_; }

std::string CpuAgent::toStdString() {
    iter_.First();
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

bool CpuAgent::SetUrl(std::string_view) { return false; }

bool setPrivilege(Privilege privilege) { return false; }