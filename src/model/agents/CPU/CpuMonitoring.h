#pragma once
#include "IAgent.h"
class CpuMonitoring : public IAgent{
    public:

    const AgentReport const* GetReport() const { return &IAgent::report_; }
    void update();
    
};