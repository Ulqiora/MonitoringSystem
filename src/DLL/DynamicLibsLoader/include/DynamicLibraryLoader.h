//
// Created by ccnc on 9/21/23.
//

#pragma once
#include <filesystem>
#include <algorithm>
#include <list>
#include <memory>
namespace Agent{
class IAgentAPI;
class DynamicLoaderLibrary{
public:
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
    };
    void downloadLibrary(const std::filesystem::directory_entry& );
    [[nodiscard]] bool isDownloaded(const std::filesystem::directory_entry& entry)const noexcept;
private:
    bool isActivated = true;
    std::list<LibraryInfo> libraries_;
    std::filesystem::path workingLibraryDirectory_;
    std::filesystem::path workingConfigDirectory_;
};
}
