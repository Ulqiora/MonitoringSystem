#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "../../AgentReportF/Builder.h"
#include "NetworkAgent.h"

NetworkAgent::NetworkAgent(IBuilder* bd)
    : info_(bd->getAgentInfo()), report_(bd->getResult()), iter_(report_) {
    info_ = bd->getAgentInfo();
    report_ = bd->getResult();
    update();
}

void NetworkAgent::update() { iter_.First(); }

[[nodiscard]] bool NetworkAgent::SetUrl(std::string_view url) {
    URL_ = url;
    return true;
}

[[nodiscard]] ReportComposite::Iterator NetworkAgent::GetReport() {
    return ReportComposite::Iterator(iter_);
}

[[nodiscard]] const InfoAgent& NetworkAgent::GetInfoAboutAgent() { return info_; }

[[nodiscard]] std::string NetworkAgent::toStdString() {
    std::stringstream ss;
    ReportComposite::Iterator iter(iter_);
    for (iter.First(); !iter.isEnd(); iter.Next()) {
        ss << std::setw(15) << std::left << (*iter).second.getValue() << '|';
    }
    return ss.str();
}

void NetworkAgent::checkUrl() {
    std::string command = "curl -I " + URL_ + " -o /dev/null -s -w '%{http_code}\n'";
    std::string output = "";
    char buffer[128];
    std::FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (!std::feof(pipe)) {
        if (std::fgets(buffer, 128, pipe) != NULL) output += buffer;
    }
    pclose(pipe);
    (*iter_).second.setValue((std::stod(output) == 200 ? 1 : 0)), iter_.Next();
}
