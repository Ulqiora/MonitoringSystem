#pragma once
#include <list>
#include <chrono>
#include <IAgentAPI.h>
#include <filesystem>
namespace Agent{
class PrinterAgentInfo{
public:
    void generateFilename();
    explicit PrinterAgentInfo(std::list<std::shared_ptr<IAgentAPI>>& libraries);
    void start();
    void setFolderForLogfiles(const std::filesystem::directory_entry&);
private:
    std::list<std::shared_ptr<IAgentAPI>>& libraries_;

    std::chrono::time_point<std::chrono::system_clock> time_;
    std::filesystem::path LogDirectory;
    std::string filepath_;
};
}
