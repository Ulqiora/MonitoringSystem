#pragma once
#include <boost/config.hpp>
#include <string>
#include <chrono>
#include <map>
#include <boost/property_tree/json_parser.hpp>
namespace Agent {
    class BOOST_SYMBOL_VISIBLE IAgentAPI {
    public:
        [[nodiscard]] virtual std::string name() const = 0;

        virtual boost::property_tree::ptree report() = 0;

        virtual void updateInfo() = 0;

//   virtual void setFileSettings(const std::string&) = 0;
        virtual ~IAgentAPI() = default;

    protected:
        std::map<std::string, std::function<bool(double, double)>> kCompareTranslator_{
                {">=", [](double a, double b) { return a >= b; }},
                {">",  [](double a, double b) { return a > b; }},
                {"<=", [](double a, double b) { return a <= b; }},
                {"<",  [](double a, double b) { return a < b; }},
                {"==", [](double a, double b) { return a == b; }},
                {"!=", [](double a, double b) { return a != b; }},
        };
    };
}