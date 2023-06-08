#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <
#include "../../AgentReportF/ReportComponent.h"
class IAgent {
   public:
    IAgent() {}
    IAgent(const IAgent&) = delete;
    IAgent(IAgent&&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    const ReportComponent const* GetReport() const { return report_; }
    virtual void update() = 0;
   private:
    ReportComponent* report_;
};
