//
// Created by ccnc on 9/21/23.
//
#include "DynamicLibraryLoader.h"
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
namespace dll = boost::dll;
namespace Agent {
    bool DynamicLoaderLibrary::isDownloaded(const std::filesystem::directory_entry &entry) const noexcept {
        return std::find_if(libraries_.cbegin(),
                            libraries_.cend(),
                            [&entry](const LibraryInfo &info) {
                                return info.libraryPath_ == entry.path();
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
                if(isNeedToUpdate(entry)){
                    updateLibrary(entry);
                }
                if(!isDownloaded(entry)){
                    downloadLibrary(entry);
                }
            }
        }
    }

    void DynamicLoaderLibrary::setState(bool state) {
        isActivated = state;
    }

    void DynamicLoaderLibrary::downloadLibrary(const std::filesystem::directory_entry & entry) {
        boost::function<std::shared_ptr<IAgentAPI>(const std::string &)> creator;
        creator = boost::dll::import_alias<std::shared_ptr<IAgentAPI>(
                const std::string &)>(             // type of imported symbol must be explicitly specified
                entry.path(),                                            // path to library
                "create_plugin",                                                // symbol to import
                dll::load_mode::append_decorations                              // do append extensions and prefixes
        );
        auto config = (workingConfigDirectory_ / entry.path().stem()).string() + ".json";
        libraries_.emplace_back(
                LibraryInfo{
                        entry.path().stem().string(),
                        config,
                        entry.path(),
                        creator(config),
                        last_write_time(entry.path())
                }
        );
    }

    bool DynamicLoaderLibrary::isNeedToUpdate(const std::filesystem::directory_entry &entry) const noexcept {
        return std::find_if(libraries_.cbegin(),
                            libraries_.cend(),
                            [&entry](const LibraryInfo& lib){
            return  std::filesystem::exists(lib.libraryPath_) &&
                    entry.last_write_time() != lib.timeLastEdited;
        }) == libraries_.cend();
    }

    void DynamicLoaderLibrary::updateLibrary(const std::filesystem::directory_entry &entry) {
        auto library = std::find_if(libraries_.begin(),
                                    libraries_.end(),
                                    [&entry](const LibraryInfo& lib){
                                        return  std::filesystem::exists(lib.libraryPath_) &&
                                                entry.last_write_time() != lib.timeLastEdited;
                                    });
        libraries_.erase(library);
        downloadLibrary(entry);
    }

    DynamicLoaderLibrary::DynamicLoaderLibrary(std::mutex & mutex) :mutex_(mutex) {

    }
}