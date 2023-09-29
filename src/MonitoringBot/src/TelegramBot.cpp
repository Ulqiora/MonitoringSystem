//
// Created by ccnc on 9/26/23.
//
#include "TelegramBot.h"

namespace Bot{
    MonitoringBot::MonitoringBot(): telegramBot_(kTelegramToken_){
        telegramBot_.getEvents().onCommand("/start",[k = &telegramBot_](const TgBot::Message::Ptr& message){
            k->getApi().sendMessage(message->chat->id,R"~( Приветствую  тебя!
                Я буду отправлять тебе информацию о текущем состоянии твоего компьютере, если это приложение включено.
            )~");
        });
    }
    void MonitoringBot::sendMessage(const std::string& message){
        telegramBot_.getApi().sendMessage(userId_,message);
        //"Не понимаю о чем ты! Но я знаю, что ты лучше всех!!!!"
    }

    void MonitoringBot::setUserId(UserId id) {
        userId_ = id;
    }

    MonitoringBot::UserId MonitoringBot::getUserId() {
        return userId_;
    }
}