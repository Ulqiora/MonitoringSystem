#pragma once
#include <tgbot/tgbot.h>
#include <thread>
namespace Bot{
class MonitoringBot{
public:
    using UserId = uint64_t;
    MonitoringBot();
    void sendMessage(const std::string&);
    void setUserId(UserId);
    UserId getUserId();
private:
    std::string kTelegramToken_ ="6531698556:AAFsCxq-XfxEeAH7gEqfJNZZeKPd2vL9Aeg";
    TgBot::Bot telegramBot_;
    UserId userId_ = 1326920778;
};
}