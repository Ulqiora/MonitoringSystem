#include "IKernelLoaderLids.h"
#include <tuple>
#include <filesystem>

class IKernelLoaderLibs{
    public:
    IKernelLoader() {
        checkedFolder_ = fs::current_path() / "agents";
        fs::create_directory(checkedFolder_);
    }
    virtual void start() = 0;
    private:
    std::tuple<
};