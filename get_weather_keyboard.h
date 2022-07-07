#include <stdio.h>
#include <string>
#include <nlohmann/json.hpp>
#include "get_request.h"

float get_weather_keyboard(char what)
{
    if (what=='m'){
        auto js_obj = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?q=Moscow&appid="+API_KEY+"));
        return js_obj["weather.main"].get<float>();
    }
    else{
        auto js_obj = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?q=Arkhangelsk&appid="+API_KEY+"));
        return js_obj["weather.main"].get<float>();
    }
    return -1;
}

