#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "../AgentReportF/Builder.h"
#include "../AgentReportF/ReportComponent.h"
class IAgent {
   public:
    IAgent(IBuilder* builder) {}
    IAgent(const IAgent&) = delete;
    IAgent(IAgent&&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    const ReportComponent const* GetReport() const { return report_; }
    virtual void update() = 0;
    virtual std::string getName(){}
   private:
    ReportComponent* report_;
    std::string name_;
    std::string typeAgent_;
    int time_seconds_;
    bool enabled_;
};
