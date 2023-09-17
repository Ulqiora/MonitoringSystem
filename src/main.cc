#include <boost/dll/import.hpp> // for import_alias
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "DLL/IAgentAPI.h"
#include <boost/function.hpp>
namespace dll = boost::dll;
#include <DynLibsLoader.h>
int main(int argc, char* argv[]) {
//    try {
//        using namespace Agent;
//        boost::dll::fs::path lib_path(
//                argv[1]);
//        std::shared_ptr<IAgentAPI> plugin;            // variable to hold a pointer to plugin variable
//        std::cout << "Loading the plugin" << std::endl;
//
//        boost::function<std::shared_ptr<IAgentAPI>(const std::string &)> creator;
//        creator = boost::dll::import_alias<std::shared_ptr<IAgentAPI>(
//                const std::string &)>(             // type of imported symbol must be explicitly specified
//                lib_path,                                            // path to library
//                "create_plugin",                                                // symbol to import
//                dll::load_mode::append_decorations                              // do append extensions and prefixes
//        );
//        std::cout << "start used\n";
//        plugin = creator("/home/ccnc/Desktop/MonitoringSystem/example.json");
//        std::cout<<plugin->name()<<'\n';
//        namespace pt = boost::property_tree;
////        std::cout<<"Point is allocated? "<<plugin->report();
//        pt::ptree report;
//        pt::read_json("/home/ccnc/Desktop/MonitoringSystem/example.json",report);
//        plugin->updateInfo();
//        report = plugin->report();
//        boost::property_tree::write_json(std::cout,report);
//    }catch (const std::exception& e){
//        std::cout<<e.what();
//    }
    Agent::DynamicLibraryLoader loader;
    loader.setWorkingDirectoryLibs("/home/ccnc/Desktop/MonitoringSystem/libs");
    loader.setWorkingDirectoryConfigs("/home/ccnc/Desktop/MonitoringSystem/configs");
    loader.startCheck();
}