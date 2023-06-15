#pragma once
#include "../IAgent.h"
#include "../InfoAgent.h"
class IBuilder;
struct InfoAgent;

class CpuAgent : public IAgent {
 public:
    CpuAgent(IBuilder* bd);
    ReportComposite::Iterator GetReport() override final;
    void update() override final;
    const InfoAgent& GetInfoAboutAgent() override final;
 private:
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};