#pragma once
#include <vector>
#include <string>
#include <string_view>
class ReportComponent;
class ReportComposite;
class ReportValue;

class IReportObserver {
 public:
    virtual void Visit(ReportComposite* component) = 0;
    virtual void Visit(ReportValue* component) = 0;
};

class IReportObserverGetWay : public IReportObserver {
 
 public:
    std::vector<std::pair<std::vector<std::string_view>,double>> result;
    void Visit(ReportComposite* component) override;
    void Visit(ReportValue* component) override {}
};