#pragma once
#include <functional>
#include <map>
#include <string>
namespace MetricParametersConstants {
static std::map<std::string, std::function<bool(double, double)> > mapOperationCompare{
    {"\"<\"", [](double v1, double v2) -> bool { return v1 < v2; }},
    {"\"<=\"", [](double v1, double v2) -> bool { return v1 <= v2; }},
    {"\">\"", [](double v1, double v2) -> bool { return v1 > v2; }},
    {"\">=\"", [](double v1, double v2) -> bool { return v1 >= v2; }},
    {"\"==\"", [](double v1, double v2) -> bool { return v1 == v2; }},
    {"\"!=\"", [](double v1, double v2) -> bool { return v1 != v2; }}};
}

class MetricParameters {
 public:
    MetricParameters(std::string type, double critvalue, double value)
        : type_(MetricParametersConstants::mapOperationCompare[type]), critical_value_(critvalue), value_(value) {}
    void setValue(double value) { value_ = value; }
    void setCriticalValue(double value) { critical_value_ = value; }
    const double& getValue() { return value_; }
    bool fdsa(){
        return type_(critical_value_,value_);
    }
 private:
    std::function<bool(double,double)> type_;
    double critical_value_;
    double value_;
};