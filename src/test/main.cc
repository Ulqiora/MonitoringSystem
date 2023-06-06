#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <vector>
using namespace std;

int main() {
    int mib[4];
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;
    mib[3] = 0;
    size_t len;
    sysctl(mib, 4, NULL, &len, NULL, 0);

    int numProcesses = len / sizeof(struct kinfo_proc);

    std::cout << "Число запущенных процессов: " << numProcesses << std::endl;
    double loadAverage[3];
    int result = getloadavg(loadAverage, 3);
    
    if (result != -1) {
        std::cout << "Загрузка процессора: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << loadAverage[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Не удалось получить информацию о загрузке процессора." << std::endl;
    }
    
    return 0;
}