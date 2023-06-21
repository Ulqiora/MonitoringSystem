#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class SystemAgent: public IAgent{
 public:
    SystemAgent(IBuilder* bd);
    void update() override final;
    [[nodiscard]] std::string toStdString() override final;
    [[nodiscard]] bool setPrivilege(Privilege) override final;
    [[nodiscard]] bool SetUrl(std::string_view) override final;
    [[nodiscard]] ReportComposite::Iterator GetReport() override final;
    [[nodiscard]] const InfoAgent& GetInfoAboutAgent() override final;
 private:
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
    Privilege priv_;
};