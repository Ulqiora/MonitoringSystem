#include <sys/sysinfo.h>

double getResult(){
    cpu_set_t cpuset;
    int num_cpus = get_nprocs();  // получение количества доступных процессоров
    double load_avg;
    if (sched_getaffinity(0, sizeof(cpuset), &cpuset) == -1) {  // получение информации об использовании процессора
        perror("sched_getaffinity");
        exit(EXIT_FAILURE);
    }
    getloadavg(&load_avg, num_cpus);  // получение средней нагрузки за последние 1, 5 и 15 минут
}