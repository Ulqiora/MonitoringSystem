#include "CpuMonitoring.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <iostream>
void CpuMonitoring::update(){
    int mib[4] = {CTL_KERN,KERN_PROC,KERN_PROC_ALL,0};
    size_t len;
    sysctl(mib, 4, NULL, &len, NULL, 0);
    int numProcesses = len / sizeof(struct kinfo_proc);
    std::cout << "Число запущенных процессов: " << numProcesses << std::endl;

    double loadAverage[3];
    int result = getloadavg(loadAverage, 3);
    if (result != -1) {
        loadAverage[0];
    } else {
        std::cout << "Не удалось получить информацию о загрузке процессора." << std::endl;
    }
}