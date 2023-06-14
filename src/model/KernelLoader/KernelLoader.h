#pragma once
#include <chrono>
#include <filesystem>
#include <vector>

#include "../agents/IAgent.h"
namespace fs=std::filesystem;
class KernelLoader {
   public:
    KernelLoader() : agents_(0) {
        checkedFolder_ = fs::current_path() / "agents";
    }
    void start() {
        for (const auto& entry : fs::directory_iterator(checkedFolder_)) {
            std::cout << entry.path() << std::endl;
            auto ftime = std::filesystem::last_write_time(entry);
            std::chrono::system_clock::time_point modTime =
                std::chrono::system_clock::time_point::clock::from_time_t(
                    std::chrono::system_clock::to_time_t(ftime));
ftime.time_since_epoch().
            // Convert the time_t to a human-readable local time
            char buff[20];
            std::strftime(buff, 20, "%Y-%m-%d %H:%M:%S",
                          std::localtime(&ftime));

            // Print the resulting time string
            std::cout << "Last modified at: " << buff << std::endl;
        }
    }

   private:
    std::vector<IAgent*> agents_;
    fs::path checkedFolder_;
};