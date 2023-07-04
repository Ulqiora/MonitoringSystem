#pragma once
#include <chrono>
#include <filesystem>
#include <vector>

namespace fs=std::filesystem;
class IKernelLoader {
   public:
    IKernelLoader() {
        checkedFolder_ = fs::current_path() / "agents";
        fs::create_directory(checkedFolder_);
    }
    virtual void start() = 0;

   private:
    fs::path checkedFolder_;
};