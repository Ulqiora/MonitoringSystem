//
// Created by ccnc on 9/21/23.
//
//#include "DynamicLibraryLoader.h"
#include "DynamicLibraryLoader.h"
#include "IAgentAPI.h"
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <chrono>
#include <mutex>
#include <format>
namespace dll = boost::dll;
namespace Agent {
    bool DynamicLoaderLibrary::isDownloaded(const std::filesystem::directory_entry &entry) const noexcept {
        return std::find_if(libraries_.cbegin(),
                            libraries_.cend(),
                            [&entry](const LibraryInfo &info) {
                                return info.getPath() == entry.path();
                            }
        ) != libraries_.cend();
    }

    void DynamicLoaderLibrary::setLibraryDirectory(const std::filesystem::path &path) {
        if(std::filesystem::exists(path))
            workingLibraryDirectory_=path;
    }
    void DynamicLoaderLibrary::setConfigDirectory(const std::filesystem::path &path) {
        if(std::filesystem::exists(path))
            workingConfigDirectory_=path;
    }

    void DynamicLoaderLibrary::start() {
        while(isActivated){
            for(const auto& entry : std::filesystem::directory_iterator(workingLibraryDirectory_)){
                if(!isDownloaded(entry)){
                    std::lock_guard lg(mutex_);
                    downloadLibrary(entry);
                    continue;
                }
                if(isNeedToUpdate(entry)){
                    std::lock_guard lg(mutex_);
                    updateLibrary(entry);
                    continue;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout<<libraries_.size()<<'\n';
        }
    }

    void DynamicLoaderLibrary::downloadLibrary(const std::filesystem::directory_entry & entry) {
        libraries_.emplace_back(
                entry.path(),workingConfigDirectory_,true
        );
    }

    bool DynamicLoaderLibrary::isNeedToUpdate(const std::filesystem::directory_entry &entry) const noexcept {
        namespace fs = std::filesystem;
        using namespace std::chrono_literals;
        return std::find_if(libraries_.cbegin(),
                            libraries_.cend(),
                            [&entry](const LibraryInfo& lib){
            return  fs::exists(lib.getPath()) &&
                    entry.path().string() == lib.getPath() &&
                    entry.last_write_time() != lib.getLastTimeEdited();
        }) != libraries_.cend();
    }

    void DynamicLoaderLibrary::updateLibrary(const std::filesystem::directory_entry &entry) {
        auto library = std::find_if(libraries_.cbegin(),
                                    libraries_.cend(),
                                    [&entry](const LibraryInfo& lib){
                                        return  std::filesystem::exists(lib.getPath()) &&
                                                entry.path().string() == lib.getPath() &&
                                                entry.last_write_time() != lib.getLastTimeEdited();
                                    });
        libraries_.erase(library);
        downloadLibrary(entry);
    }

    DynamicLoaderLibrary::DynamicLoaderLibrary(std::mutex & mutex) :mutex_(mutex) {}

    void DynamicLoaderLibrary::off() {
        std::lock_guard lg(mutex_);
        isActivated =  false;
    }

    DynamicLoaderLibrary::LibraryInfo::LibraryInfo(const std::filesystem::path &filePath,
                                                   const std::filesystem::path &configFolder,
                                                   bool activated):
            activate_(activated),
            filename_(filePath.string()),
            configPath_((configFolder / filePath.stem()).string() + ".json"),
            agent_(nullptr),
            timeLastEdited_(std::filesystem::last_write_time(filePath)),
            timeOfLoad_(std::chrono::system_clock::now())
    {
        boost::function<std::shared_ptr<IAgentAPI>(const std::string &)> creator;
        boost::filesystem::path temp(filename_);
        creator = boost::dll::import_alias<std::shared_ptr<IAgentAPI>(const std::string &)>(
                temp,
                "create_plugin",
                boost::dll::load_mode::append_decorations
        );
        agent_ = creator(configPath_);
    }

    std::string_view DynamicLoaderLibrary::LibraryInfo::getPath() const {
        return filename_;
    }

    void DynamicLoaderLibrary::LibraryInfo::update() {
        agent_->updateInfo();
        timeOfLoad_+= agent_->getInterval();
    }

    const std::filesystem::file_time_type &DynamicLoaderLibrary::LibraryInfo::getLastTimeEdited() const {
        return timeLastEdited_;
    }
}