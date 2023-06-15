#pragma once
#include <filesystem>
#include <fstream>
#include "../Agents/InfoAgent.h"
#include "../../libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
class ReportComponent;
class ReportComposite;
namespace fs = std::filesystem;
class IBuilder {
 public:
    virtual ReportComponent* getResult() = 0;
    virtual const InfoAgent& getAgentInfo() = 0; 
 private:
    virtual void byJson(json&& filejson) = 0;
};
class Builder : public IBuilder {
 public:
    Builder(fs::path path);
    ReportComponent* getResult() override final { return (ReportComponent*)temp_; }
    const InfoAgent& getAgentInfo() override final { return info_;}

 private:
    void byJson(json&& filejson) override final;
    void byJson(json&& filejson, ReportComposite* curNode);
    ReportComposite* temp_;
    InfoAgent info_;
};