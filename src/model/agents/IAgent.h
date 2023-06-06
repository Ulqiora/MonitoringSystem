#pragma once 
#include <vector>
#include <string>
#include <string_view>
class IAgent{
    public:
        IAgent(){}
        IAgent(const IAgent&) = delete;
        IAgent(IAgent&&) = delete;
        IAgent& operator=(const IAgent&) = delete;
        IAgent& operator=(const IAgent&) = delete;
    private:
    std::vector<std::pair<std::string,double>> 
}