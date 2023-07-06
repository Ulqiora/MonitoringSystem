#include "IKernelLoader.h"
#include <tuple>
#include <chrono>

class KernelLoaderLibs : public IKernelLoader {
   public:
    KernelLoaderLibs(fs::path worked_path) {
        checkedFolder_ = worked_path / "agents";
        fs::create_directory(checkedFolder_);
    }
    virtual void start() override {
        using namespace std::chrono_literals;
        using namespace std::chrono;
        for (const auto& entry : fs::directory_iterator(checkedFolder_)) {
            std::cout << entry.path() << std::endl;
            auto ftime = std::filesystem::last_write_time(entry);
            auto cftime  = time_point_cast<system_clock::duration>(ftime  - decltype(ftime)::clock::now() + system_clock::now());
            auto tt = system_clock::to_time_t(cftime);
            // const auto time = std::chrono::system_clock::to_time_t(systemTime);
            // std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
            // std::chrono::system_clock::time_point modTime =
            //     std::chrono::system_clock::time_point::clock::from_time_t(
            //         std::chrono::system_clock::to_time_t(ftime));
            // ftime.time_since_epoch().
            //     // Convert the time_t to a human-readable local time
                char buff[20];
            std::strftime(buff, 20, "%Y-%m-%d %H:%M:%S",
                          std::localtime(&tt));

            // // Print the resulting time string
            std::cout << "Last modified at: " << buff << std::endl;
        }
    }

   private:
    // std::tuple<
};