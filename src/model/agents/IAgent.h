#pragma once
#include "../AgentReportF/ReportComponent.h"
struct InfoAgent;
class IAgent {
   public:
    IAgent(const IAgent&) = delete;
    IAgent(IAgent&&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    virtual ReportComposite::Iterator GetReport() = 0;
    virtual void update() = 0;
    virtual InfoAgent GetInfoAboutAgent();
};
