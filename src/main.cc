// #include <cstdio>
// #include <fstream>
// #include <iostream>
// #include <string>
// #include <thread>
// #include <vector>
// // #include <sys/param.h>
// // #include <sys/mount.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <sys/vfs.h>
// #include <sys/types.h>
// #include <sys/sysinfo.h>
// // #include "libs/json/single_include/nlohmann/json.hpp"
// // #include "model/AgentReportF/Builder.h"
// // #include "model/AgentReportF/ReportComponent.h"
// // #include "model/Agents/CPU/CpuAgent.h"
// using namespace std;
// // using json = nlohmann::json;
// int main() {
//     int num_processes = sysconf(_SC_NPROCESSORS_ONLN);
//     std::cout << "Number of processes: " << num_processes << std::endl;
//         struct sysinfo si;
//     if (sysinfo(&si) == 0) {
//         std::cout << "Total RAM: " << si.totalram / 1024 / 1024 << " MB" << std::endl;
//     }
//     if (sysinfo(&si) == 0) {
//         double used_mem = si.totalram - si.freeram;
//         double mem_percent = used_mem / si.totalram * 100.0;
//         cout << "Memory usage: " << mem_percent << "%" << endl;
//     }









//     //     struct statfs fs_info;
//     // int error = statfs("/", &fs_info);

//     // if (error != 0) {
//     //     std::cerr << "Error: " << strerror(errno) << std::endl;
//     //     return 1;
//     // }

//     // double disk_size = static_cast<double>(fs_info.f_bsize * fs_info.f_blocks) / (1024 * 1024 * 1024); // размер диска в Гб
//     // double free_space = static_cast<double>(fs_info.f_bsize * fs_info.f_bfree) / (1024 * 1024 * 1024); // свободное место в Гб
//     // double used_space = disk_size - free_space; // занятое место в Гб
//     // double io_time = 1.0 / (fs_info.f_iosize / 1000.0 / 1000.0); // время на I/O операции в секундах
//     // double max_throughput = used_space / io_time; // максимальная пропускная способность в Гб/с

//     // std::cout << "Disk size: " << disk_size << " GB";
//     // std::cout << "Free space: " << free_space << " GB";
//     // std::cout << "Used space: " << used_space << " GB";
//     // std::cout << "Maximum throughput: " << max_throughput << " GB/s";

//     // return 0;
//     /* Закрываем поток */
//     // fs::path path = fs::current_path()/"example.json";
//     // IBuilder* bd = new Builder(path);
//     // IAgent* agent=new CpuAgent(bd);
//     // agent->update();
//     // agent->update();
//     // for (ReportComposite::Iterator iter(agent->GetReport()); !iter.isEnd(); iter.Next()) {
//     //     auto report_i = (*iter);
//     //     for (auto& point : report_i.first) {
//     //         std::cout << point << std::endl;
//     //     }
//     //     std::cout << "value = "<<report_i.second.getValue() << std::endl;
//     //     std::cout << "critical value = "<< report_i.second.getCriticalValue() << std::endl;
//     //     std::cout << "Result compare = "<< report_i.second.compareIsTrue() << std::endl;
//     // }

//     // auto firstNodeLevel  = bd->getResult();
//     // std::cout<<"Agent name : "<<bd->getAgentInfo().name_<<'\n';
//     // std::cout<<"Agent type : "<<bd->getAgentInfo().typeAgent_<<'\n';
//     // std::cout<<"Agent interval : "<<bd->getAgentInfo().time_seconds_<<'\n';
//     // std::cout<<"Agent enabled : "<<bd->getAgentInfo().enabled_<<'\n';
//     // for (ReportComposite::Iterator iter(firstNodeLevel); !iter.isEnd(); iter.Next()) {
//     //     auto report_i = (*iter);
//     //     for (auto& point : report_i.first) {
//     //         std::cout << point << std::endl;
//     //     }
//     //     std::cout << "value = "<<report_i.second.getValue() << std::endl;
//     //     std::cout << "critical value = "<< report_i.second.getCriticalValue() << std::endl;
//     //     std::cout << "Result compare = "<< report_i.second.compareIsTrue() << std::endl;
//     // }
// }
// #include <fstream>
// #include <iostream>
// #include <string>

// int main() {
//     std::ifstream diskstats("/proc/diskstats");
//     std::string line;

//     while (std::getline(diskstats, line)) {
//         if (line.find("sda") != std::string::npos) {
//             long long reads, writes;
//             sscanf(line.c_str(), "   8   0 %*s %lld %*d %lld", &reads, &writes);
//             std::cout << "Reads: " << reads << " Writes: " << writes << std::endl;
//             break;
//         }
//     }

//     return 0;
// }
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main() {
    int fd = open("/dev/sda", O_RDONLY);
    uint64_t block_size;

    // запрос размера блока устройства
    if (ioctl(fd, BLKGETSIZE64, &block_size) == -1) {
        std::cerr << "Ошибка при получении размера блока!" << std::endl;
        return 1;
    }
    
    // симуляция операции ввода/вывода
    char buffer[1024];
    ssize_t nbytes = read(fd, buffer, 1024);
    if (nbytes == -1) {
        std::cerr << "Ошибка ввода/вывода!" << std::endl;
        return 1;
    }

    // вывод количества переданных байт
    uint64_t io_size = nbytes * block_size;
    std::cout << "Передано " << io_size << " байт" << std::endl;

    close(fd);
    return 0;
}