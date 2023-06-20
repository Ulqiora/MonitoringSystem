#pragma once
#include <functional>
#include <map>
#include <string>
namespace MetricParametersConstants {
static std::map<std::string, std::function<bool(double, double)> >
    mapOperationCompare{
        {"<", [](double v1, double v2) -> bool { return v1 < v2; }},
        {"<=", [](double v1, double v2) -> bool { return v1 <= v2; }},
        {">", [](double v1, double v2) -> bool { return v1 > v2; }},
        {">=", [](double v1, double v2) -> bool { return v1 >= v2; }},
        {"==", [](double v1, double v2) -> bool { return v1 == v2; }},
        {"!=", [](double v1, double v2) -> bool { return v1 != v2; }}};
}

class MetricParameters {
   public:
    MetricParameters(std::string type, double critvalue, double value)
        : value_(value),
          critical_value_(critvalue),
          type_(MetricParametersConstants::mapOperationCompare[type]) {}
    void setValue(double value) { value_ = value; }
    void setCriticalValue(double value) { critical_value_ = value; }
    const double& getValue() { return value_; }
    const double& getCriticalValue() { return critical_value_; }
    bool compareIsTrue() { return type_(critical_value_, value_); }

   private:
    double value_ = 0.0;
    double critical_value_ = 0.0;
    std::function<bool(double, double)> type_;
};