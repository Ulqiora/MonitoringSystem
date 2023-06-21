#pragma once
#include "../IAgent.h"
#include "../InfoAgent.h"
#include <sstream>
#include <iomanip>
class IBuilder;
struct InfoAgent;

class CpuAgent : public IAgent {
 public:
    CpuAgent(IBuilder* bd);
    void update() override final;
    [[nodiscard]] std::string toStdString() override final;
    [[nodiscard]] bool setPrivilege(Privilege) override final;
    [[nodiscard]] bool SetUrl(std::string_view) override final;
    [[nodiscard]] const InfoAgent& GetInfoAboutAgent() override final;
    [[nodiscard]] ReportComposite::Iterator GetReport() override final;
 private:
   	void getCpuLoaded();
	void getNumProc();
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};