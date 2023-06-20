#pragma once
#include <chrono>
#include "../AgentReportF/ReportComponent.h"
struct InfoAgent;
class IAgent {
 public:
    IAgent() = default;
    IAgent(const IAgent&) = delete;
    IAgent(IAgent&&) = delete;
    IAgent& operator=(const IAgent&) = delete;
    IAgent& operator=(IAgent&&) = delete;

    virtual void update() = 0;
    virtual ReportComposite::Iterator GetReport() = 0;
    virtual const InfoAgent& GetInfoAboutAgent() = 0;
    virtual std::string toStdString() = 0;
    virtual bool SetUrl(std::string_view) = 0;
};
