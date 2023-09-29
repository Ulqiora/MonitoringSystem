#include "PrinterAgentInfo.h"

namespace Agent{
PrinterAgentInfo::PrinterAgentInfo(std::list<std::shared_ptr<IAgentAPI>>& libraries) :
                    libraries_(libraries) {}

void PrinterAgentInfo::start() {
    while(true){
        for(auto& library : libraries_){

        }
    }
}

void PrinterAgentInfo::setFolderForLogfiles(const std::filesystem::directory_entry &entry) {
    if(std::filesystem::exists(entry))
        LogDirectory = entry.path();
}

void PrinterAgentInfo::generateFilename() {
    time_ = (std::chrono::system_clock::now());
    std::chrono::year_month_day ymd(std::chrono::floor<std::chrono::days>(time_));
    filepath_ = std::to_string(static_cast<int>(ymd.year())) + "-" +
            std::to_string(static_cast<unsigned>(ymd.month())) + "-" +
            std::to_string(static_cast<unsigned>(ymd.day())) + ".log";
    filepath_ = LogDirectory/filepath_;
}
}
