#pragma once
#include "../IAgent.h"

class CpuMonitoring : public IAgent{
    public:
    // CpuMonitoring
    void update()override{

    }
    private:
    ReportComponent* report_;

};