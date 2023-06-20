#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class MemoryAgent : public IAgent {
 public:
    MemoryAgent(IBuilder* bd);
    void update() override final;
    [[nodiscard]] bool SetUrl(std::string_view) override final;
    [[nodiscard]] ReportComposite::Iterator GetReport() override final;
    [[nodiscard]] const InfoAgent& GetInfoAboutAgent() override final;
    [[nodiscard]] std::string toStdString() override final;

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