#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class MemoryAgent : public IAgent {
 public:
    MemoryAgent(IBuilder* bd);
    ReportComposite::Iterator GetReport() override final;
    void update() override final;
    const InfoAgent& GetInfoAboutAgent() override final;

 private:
    void setRamTotal();
    void setRamPercent();
	void setHardVolume();
	void setHardOps();
	void setHardThroughput();

    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};