//
// Created by ccnc on 9/21/23.
//

#pragma once
#include <filesystem>
#include <algorithm>
#include <list>
#include <memory>
#include <thread>
#include <mutex>
namespace Agent{
class IAgentAPI;
class DynamicLoaderLibrary{
public:
    DynamicLoaderLibrary(std::mutex&);

    void setLibraryDirectory(const std::filesystem::path&);
    void setConfigDirectory(const std::filesystem::path&);
    void start();
    void setState(bool );
private:
    struct LibraryInfo{
        std::string filename_;
        std::filesystem::path configPath_;
        std::filesystem::path libraryPath_;
        std::shared_ptr<IAgentAPI> agent_;
        std::filesystem::file_time_type timeLastEdited;
    };
    void updateLibrary(const std::filesystem::directory_entry&);
    void downloadLibrary(const std::filesystem::directory_entry& );
    [[nodiscard]] bool isDownloaded(const std::filesystem::directory_entry& entry)const noexcept;
    [[nodiscard]] bool isNeedToUpdate(const std::filesystem::directory_entry& entry)const noexcept;
private:
    std::mutex& mutex_;
    bool isActivated = true;
    std::list<LibraryInfo> libraries_;
    std::filesystem::path workingLibraryDirectory_;
    std::filesystem::path workingConfigDirectory_;
};
}
