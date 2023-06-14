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
    IBuilder(fs::path path) {
        std::ifstream file(path);
        if (!file.is_open()) throw std::invalid_argument("Incorrect file!");
        json filejson = json::parse(file);
        byJson(filejson);
    }
    virtual ReportComponent* getResult() = 0;
    virtual std::string getName() = 0;
    virtual std::string getType() = 0;
    virtual std::string getTime() = 0;
    virtual std::string isenabled() = 0;
 private:
    virtual void byJson(json filejson) = 0;
};
class Builder : IBuilder {
 public:
    Builder(fs::path path) : IBuilder(path) {}
    ReportComponent* getResult() override final { return (ReportComponent*)temp_; }

 private:
    void byJson(json filejson) override final;
    void byJson(json& filejson, ReportComposite* curNode);
    ReportComposite* temp_;
    std::string name_;
    std::string typeAgent_;
    int time_seconds_;
    bool enabled_;
};