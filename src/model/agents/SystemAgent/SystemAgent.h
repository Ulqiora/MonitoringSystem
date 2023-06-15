#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class SystemAgent: public IAgent{
 public:
    SystemAgent(IBuilder* bd);
    ReportComposite::Iterator GetReport() override final;
    void update() override final;
    const InfoAgent& GetInfoAboutAgent() override final;
 private:
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};