#pragma once

#include "../IAgent.h"
#include "../InfoAgent.h"

class IBuilder;
class SystemAgent: public IAgent{
 public:
    SystemAgent(IBuilder* bd);
    void update() override final;
    [[nodiscard]] std::string toStdString() override final;
    [[nodiscard]] bool SetUrl(std::string_view) override final;
    [[nodiscard]] ReportComposite::Iterator GetReport() override final;
    [[nodiscard]] const InfoAgent& GetInfoAboutAgent() override final;
 private:
	void setPrivileges();
	void setTotalSwap();
	void setUsedSwap();
	void setProcQueuelength();
	void setVirtualMemVolume();
	void setVirtualMemFree();
	void setInodes();
	void setHardReadTime();
	void setSystemErrors();
	void setUserAuths();
	
    InfoAgent info_;
    ReportComponent* report_;
    ReportComposite::Iterator iter_;
};