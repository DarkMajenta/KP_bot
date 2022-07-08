#ifndef GET_WEATHER_KEYBOARD_H
#define GET_WEATHER_KEYBOARD_H
#include <stdio.h>
#include <string>
#include <nlohmann/json.hpp>
#include "get_request.h"

using namespace std;

float get_weather_keyboard(char what)
{
    if (what=='m'){
        auto js_obj = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?q=Moscow&appid=API_KEY"));
        return js_obj["main"]["temp"].get<float>()-273; //Celcius
    }
    if (what == 'a'){
        auto js_obj = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?q=Arkhangelsk&appid=API_KEY"));
        return js_obj["main"]["temp"].get<float>()-273;//Celcius
    }
    return -1;
}
#endif
