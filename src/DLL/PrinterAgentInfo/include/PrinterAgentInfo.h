#pragma once
#include <list>
#include <chrono>
#include <IAgentAPI.h>
#include <filesystem>
namespace Agent{
class PrinterAgentInfo{
public:

    explicit PrinterAgentInfo(std::list<std::shared_ptr<IAgentAPI>>& libraries,std::mutex& mutex);

    [[noreturn]] void start();
    void setFolderForLogfiles(const std::filesystem::directory_entry&);
private:
    void generateFilename();
    static void updateYmd(std::chrono::year_month_day& ymd);
private:
    std::mutex& mutex_;
    std::list<std::shared_ptr<IAgentAPI>>& libraries_;
    std::chrono::year_month_day time_{};
    std::filesystem::path LogDirectory;
    std::string filepath_;
};
}
