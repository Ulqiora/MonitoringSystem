#include <boost/dll/import.hpp> // for import_alias
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "DLL/IAgentAPI.h"
#include <boost/function.hpp>
namespace dll = boost::dll;
#include <DynamicLibraryLoader.h>
//#include <tgbot/tgbot.h>
#include <TelegramBot.h>
int main(int argc, char* argv[]) {
    Bot::MonitoringBot bot;
    bot.sendMessage();
    return 0;
//    std::mutex mutex;
//    Agent::DynamicLoaderLibrary loader(mutex);
//    loader.setLibraryDirectory("/home/ccnc/Desktop/MonitoringSystem/libs");
//    loader.setConfigDirectory("/home/ccnc/Desktop/MonitoringSystem/configs");
//    loader.start();
}