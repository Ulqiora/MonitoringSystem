#include "../include/AgentCPU.h"
#include "AgentCPU.h"
#include <memory>
#include <iostream>

namespace Agent{
void AgentCPU::setFileSettings(const std::string &file_settings) {
    namespace pt = boost::property_tree;
    pt::read_json(file_settings, dataFile_);
    enabled_ = dataFile_.get<bool>("enabled");
    timeReload_ = std::chrono::seconds(dataFile_.get<int64_t>("interval"));
    createReportFormatByFile();
}

AgentCPU::AgentCPU() {
    dataFile_.clear();
    setFileSettings(fileSettings_);
}

std::shared_ptr<IAgentAPI> AgentCPU::create(const std::string &filename) {
    return std::shared_ptr<IAgentAPI>(new AgentCPU(filename));
//return nullptr;
}

std::string AgentCPU::name() const {
    return fileSettings_;
}

AgentCPU::AgentCPU(const std::filesystem::path &file_settings) : fileSettings_(file_settings.filename().c_str()) {
    setFileSettings(file_settings);
}

void AgentCPU::createReportFormatByFile() {
    namespace pt = boost::property_tree;
    pt::ptree metrics;
    for (const auto &metric: dataFile_.get_child("metrics")) {
        pt::ptree newMetric;
        newMetric.put("value", 0);
        newMetric.put("is_critical", false);
        metrics.push_back(std::make_pair(metric.first, newMetric));
    }
    report_.add_child("metrics", metrics);
//    report_->add("enabled",e);
}

void AgentCPU::updateInfo() {
    updateGpuLoadedInfo();
    updateProcessNumber();
}

void AgentCPU::updateGpuLoadedInfo() {
    std::ifstream stat_stream("/proc/stat");
    std::string line;
    std::getline(stat_stream, line);
    long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    std::sscanf(line.c_str(), "cpu %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle,
                &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
    auto total_time = (double) (user + nice + system + idle + iowait + irq + softirq + steal);
    auto idle_time = (double) (idle + iowait);
    auto result = 1.0 - idle_time / total_time;
    report_.put("metrics.cpu.value", result);
    report_.put("metrics.cpu.is_critical",
                kCompareTranslator_[dataFile_.get<std::string>("metrics.cpu.comparison")]
                        (result, dataFile_.get<double>("metrics.cpu.critical_value")));
    stat_stream.close();
}

void AgentCPU::updateProcessNumber() {
    const static std::string command = "ps aux | wc -l";
    const static std::string kMetricName = "metrics.processes";
    FILE *file = popen(command.c_str(), "r");
    if (!file) {
        throw std::bad_function_call();
    }
    char buffer[128] = "";
    if (std::fgets(buffer, sizeof(buffer), file) == nullptr)
        return;
    pclose(file);
    auto result = std::stod(buffer);

    std::cout << result << '\n';
    report_.put(kMetricName + ".value", result);
    report_.put(kMetricName + ".is_critical",
                kCompareTranslator_[dataFile_.get<std::string>(kMetricName + ".comparison")]
                        (result, dataFile_.get<double>(kMetricName + ".critical_value")));
}

}