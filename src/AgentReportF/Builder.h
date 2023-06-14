#pragma once
#include "../libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
class ReportComponent;
class ReportComposite;
class IBuilder{
    public:
    virtual void byJson(json filejson) = 0;
    virtual ReportComponent* getResult() = 0;
};
class Builder : IBuilder{
    private:
    void byJson(json& filejson, ReportComposite* curNode);
    ReportComposite* temp_;
    std::string name_;
    std::string typeAgent_;
    int time_seconds_;
    bool enabled_;
    public:
    void byJson(json filejson)override final;
    ReportComponent* getResult()override final{return (ReportComponent*)temp_;}

};