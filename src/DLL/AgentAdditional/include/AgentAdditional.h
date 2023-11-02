#pragma once

#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <string>
#include <filesystem>
#include "IAgentAPI.h"

//#include
namespace Agent {
class AgentAdditional : public IAgentAPI {
    void setFileSettings(const std::string& );
    void createReportFormatByFile();
    void updateGpuLoadedInfo();
    void updateProcessNumber();
public:
    AgentAdditional();
    explicit AgentAdditional(const std::filesystem::path&);
    [[nodiscard]] std::string name() const override;
    boost::property_tree::ptree report() final {return report_;}
    ~AgentAdditional() override = default;
    static std::shared_ptr<IAgentAPI> create(const std::string&);
    void updateInfo() override ;
private:
    std::string fileSettings_ = "AgentCPU.json";
    bool enabled_ = true;
    std::chrono::seconds timeReload_{};
    boost::property_tree::ptree dataFile_{};
    boost::property_tree::ptree report_{};
};

BOOST_DLL_ALIAS(
        Agent::AgentCPU::create, // <-- this function is exported with...
        create_plugin             // <-- ...this alias name
)
}  // namespace Agents
