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
#include <atomic>
namespace Agent{
class IAgentAPI;
class DynamicLoaderLibrary{
public:
    explicit DynamicLoaderLibrary(std::mutex&);
    void setLibraryDirectory(const std::filesystem::path&);
    void setConfigDirectory(const std::filesystem::path&);
    void start();
private:
    class LibraryInfo{
    public:
        LibraryInfo(const std::filesystem::path& filePath,
                    const std::filesystem::path& configFolder,
                    bool activated = true);
        void update();
        [[nodiscard]] std::string_view getPath() const;
        [[nodiscard]] const std::filesystem::file_time_type& getLastTimeEdited()const;
    private:
        bool activate_;
        std::string filename_;
        std::filesystem::path configPath_;
        std::shared_ptr<IAgentAPI> agent_;
        std::filesystem::file_time_type timeLastEdited_;
        std::chrono::time_point<std::chrono::system_clock> timeOfLoad_;
    };
    void updateLibrary(const std::filesystem::directory_entry&);
    void downloadLibrary(const std::filesystem::directory_entry& );
    void off();
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
