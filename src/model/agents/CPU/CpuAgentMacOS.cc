#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "../../AgentReportF/Builder.h"
#include "CpuAgent.h"

CpuAgent::CpuAgent(IBuilder* bd)
    :   info_(bd->getAgentInfo()),
        report_(bd->getResult()), iter_(report_) {
    info_ = bd->getAgentInfo();
    report_ = bd->getResult();
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
ReportComposite::Iterator CpuAgent::GetReport() {return ReportComposite::Iterator(iter_);}
const InfoAgent& CpuAgent::GetInfoAboutAgent() {return info_;}