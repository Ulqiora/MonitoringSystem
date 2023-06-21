#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class NetworkAgent : public IAgent {
 public:
    NetworkAgent(IBuilder* bd);
    void update() override final;
    [[nodiscard]] std::string toStdString() override final;
    [[nodiscard]] bool SetUrl(std::string_view) override final;
    [[nodiscard]] ReportComposite::Iterator GetReport() override final;
    [[nodiscard]] const InfoAgent& GetInfoAboutAgent() override final;

 private:
    void checkUrl();
    void getSpeedNetInterface();

    std::string URL_;
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};
