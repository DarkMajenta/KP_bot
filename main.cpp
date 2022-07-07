//BIG THX: https://youtu.be/dwij9ZytWbQ
//         https://www.youtube.com/channel/UCu60M9W_SX-SNo53CDNVJ4w
//         https://github.com/reo7sp/tgbot-cpp
//         https://stackoverflow.com/questions/36702888/download-an-image-from-an-url-using-curl-in-c
//         https://stackoverflow.com/questions/36693792/text-parser-c-code#36696232
//         https://stackoverflow.com/questions/46261431/parsing-through-text-file-with-c
//         https://stackoverflow.com/questions/9551014/reading-parsing-text-file-input-c
//         https://www.cplusplus.com/forum/beginner/879/
//         https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include "get_weather.h"
#include "get_currency.h"
#include "get_time_as_str.h"
#include "download_jpeg.h"
#include "get_weather_keyboard.h"

using namespace std;
using namespace TgBot;

vector<string> bot_commands= {"start", "echo", "time", "currency", "random_cat", "weather", "weather_text"};


int main()
{
    Bot bot("API_KEY");
    const string photoFilePath = "out.jpg";
    const string photoMimeType = "image/jpeg";

    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row0;
    InlineKeyboardButton::Ptr usd_btn(new InlineKeyboardButton), kazah_peso(new InlineKeyboardButton);
    usd_btn -> text = "USD";
    usd_btn->callbackData = "USD";
    kazah_peso -> text = "Kazah_peso";
    kazah_peso -> callbackData = "Kazahstan Peso";
    row0.push_back(usd_btn);
    row0.push_back(kazah_peso);
    keyboard->inlineKeyboard.push_back(row0);


    InlineKeyboardMarkup::Ptr keyboard2(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row1;
    InlineKeyboardButton::Ptr msk_btn(new InlineKeyboardButton), arh_btn(new InlineKeyboardButton);
    msk_btn -> text = "MSK weather";
    arh_btn->callbackData = "ARH weather";
    kazah_peso -> text = "MSK weather";
    kazah_peso -> callbackData = "ARH weather";
    row1.push_back(msk_btn);
    row1.push_back(arh_btn);
    keyboard->inlineKeyboard.push_back(row1);


    bot.getEvents().onCommand("start", [&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "Wake up "+ message->chat->firstName);
    });

    bot.getEvents().onCommand("time", [&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "MSC time: "+get_time_as_str());
    });


    bot.getEvents().onCommand("echo", [&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "It's a echo. \n Ping \n Pong!");
    });

    bot.getEvents().onCommand("random_cat", [&bot, &photoFilePath, &photoMimeType](Message::Ptr message) {
        download_jpeg("https://thiscatdoesnotexist.com/");
        bot.getApi().sendPhoto(message->chat->id, InputFile::fromFile(photoFilePath, photoMimeType));
    });

    bot.getEvents().onCommand("currency", [&bot,&keyboard](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "How currency?", false, 0, keyboard);
    });

    bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
        if (query->data == "USD")
        {
            bot.getApi().sendMessage(query->message->chat->id, to_string(get_currency('u')));
        }
        else
        {
            bot.getApi().sendMessage(query->message->chat->id, to_string(get_currency('k')));
        }
    });


    bot.getEvents().onCommand("weather_text",[&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "City?");
        bot.getEvents().onNonCommandMessage([&bot](Message::Ptr message){
            bot.getApi().sendMessage(message->chat->id, to_string(get_weather(message->text)));
        }
        );
    });
    bot.getEvents().onCommand("weather", [&bot, &keyboard2](Message::Ptr message){
        bot.getApi().sendMessage(message->chat->id, "Weather in..?", false, 0, keyboard2);
    });
    bot.getEvents().onCallbackQuery([&bot, &keyboard2](CallbackQuery::Ptr query){
        if (query->data == "MSK weather"){
            bot.getApi().sendMessage(query->message->chat->id, to_string(get_weather_keyboard('m')));
        }
        else{
            bot.getApi().sendMessage(query->message->chat->id, to_string(get_weather_keyboard('a')));
        }
    });

    bot.getEvents().onAnyMessage([&bot](Message::Ptr message)
    {
        printf("User %s wrote %s\n",message->chat->username.c_str(), message->text.c_str());
        for(const auto& command : bot_commands)
        {
            if ("/"+command==message->text)
                return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text + ". And isn't a command owo");
    });


    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgException& e)
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}




//=================================================================
//    <one line to give the program's name and a brief idea of what it does.>
//    Copyright (C) <year>  <name of author>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
