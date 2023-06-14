#pragma once
#include <filesystem>
#include <fstream>

#include "../../libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
class ReportComponent;
class ReportComposite;
namespace fs = std::filesystem;
class IBuilder {
   public:
    IBuilder(fs::path [[maybe_unused]]path){}
    virtual ReportComponent* getResult() = 0;
    virtual std::string getName() = 0;
    virtual std::string getType() = 0;
    virtual int getTime() = 0;
    virtual bool isEnabled() = 0;

   private:
    virtual void byJson(json filejson) = 0;

};
class Builder : public IBuilder {
   public:
    Builder(fs::path path) : IBuilder(path) {
         std::ifstream file(path);
        if (!file.is_open()) throw std::invalid_argument("Incorrect file!");
        json filejson = json::parse(file);
        byJson(filejson);
    }
    ReportComponent* getResult() override final {
        return (ReportComponent*)temp_;
    }
    virtual std::string getName() override final { return name_; }
    virtual std::string getType() override final { return typeAgent_; }
    virtual int getTime() override final { return time_seconds_; }
    virtual bool isEnabled() override final {return enabled_;}

   private:
    void byJson(json filejson) override final;
    void byJson(json& filejson, ReportComposite* curNode);
    ReportComposite* temp_;
    std::string name_;
    std::string typeAgent_;
    int time_seconds_;
    bool enabled_;
};