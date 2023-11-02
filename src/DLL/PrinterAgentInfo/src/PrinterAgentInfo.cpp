#include "PrinterAgentInfo.h"
#include <iostream>
#include <thread>
namespace Agent{
PrinterAgentInfo::PrinterAgentInfo(std::list<std::shared_ptr<IAgentAPI>>& libraries,std::mutex& mutex) :
                    libraries_(libraries),mutex_(mutex) {
    updateYmd(time_);
}

[[noreturn]] void PrinterAgentInfo::start() {
    std::chrono::year_month_day currentDate{};
    while(true){
        updateYmd(currentDate);
        if(currentDate == time_)
            generateFilename();
        for(auto& library : libraries_){
            std::lock_guard lg(mutex_);
            library->updateInfo();
            boost::property_tree::write_json(std::cout,library->report()) ;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void PrinterAgentInfo::setFolderForLogfiles(const std::filesystem::directory_entry &entry) {
    if(std::filesystem::exists(entry))
        LogDirectory = entry.path();
}

void PrinterAgentInfo::generateFilename() {
    updateYmd(time_);
    filepath_ = LogDirectory/(std::to_string(static_cast<int>(time_.year())) + "-" +
                              std::to_string(static_cast<unsigned>(time_.month())) + "-" +
                              std::to_string(static_cast<unsigned>(time_.day())) + ".log");
}
void PrinterAgentInfo::updateYmd(std::chrono::year_month_day& ymd){
    ymd = std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now()
    );
}
bool operator==(std::chrono::year_month_day  first,std::chrono::year_month_day second){
    return  first.day() == second.day() &&
            first.month() == second.month() &&
            first.year() == second.year();
}
}
