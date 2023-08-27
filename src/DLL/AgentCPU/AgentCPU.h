#ifndef BOOST_DLL_AGENTCPU_HPP
#define BOOST_DLL_AGENTCPU_HPP
#include <boost/config.hpp>
#include <string>

#include "../IAgentAPI.h"
namespace Agents {
class AgentCPU : public IAgentAPI {
   public:
    virtual std::string name() const { return "fdsagres"; }
    virtual void report() {}

    virtual ~AgentCPU() {}
};
extern "C" BOOST_SYMBOL_EXPORT AgentCPU plugin;
AgentCPU plugin;
}  // namespace Agents
#endif  // BOOST_DLL_IAGENTAPI_HPP
