#pragma once
#include "../libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
class ReportComponent;
class IBuilder{
    public:
    virtual void byJson(const json& filejson) = 0;
    virtual ReportComponent* getResult() = 0;
    private:
    ReportComponent* temp_;
};
class Builder : IBuilder{
    public:
    void byJson(const json& filejson)override final;
    ReportComponent* getResult()override final{return temp_;}
    private:
    void byJson(const json& filejson, ReportComponent* curNode);
    ReportComponent* temp_;
};