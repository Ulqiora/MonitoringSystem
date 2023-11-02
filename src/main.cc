#include <boost/dll/import.hpp> // for import_alias
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "DLL/IAgentAPI.h"
#include <boost/function.hpp>
namespace dll = boost::dll;
#include <DynamicLibraryLoader.h>
int main(int argc, char* argv[]) {
    setenv("LANG", "en_US.UTF-8", 1);
    std::mutex mutex;
    Agent::DynamicLoaderLibrary loader(mutex);
    loader.setLibraryDirectory("/home/ccnc/Desktop/MonitoringSystem/libs");
    loader.setConfigDirectory("/home/ccnc/Desktop/MonitoringSystem/configs");
    loader.start();


}