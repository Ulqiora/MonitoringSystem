#ifndef BOOST_DLL_IAGENTAPI_HPP
#define BOOST_DLL_IAGENTAPI_HPP
#include <boost/config.hpp>
#include <string>

class BOOST_SYMBOL_VISIBLE IAgentAPI {
public:
   virtual std::string name() const = 0;
   virtual void report()= 0;

   virtual ~IAgentAPI() {}
};
#endif // BOOST_DLL_IAGENTAPI_HPP