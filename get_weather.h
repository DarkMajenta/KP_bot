#ifndef GET_WEATHER_H
#define GET_WEATHER_H
#include <stdio.h>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "get_request.h"

using namespace std;

float get_weather(string city)
{
        string link = "https://api.openweathermap.org/data/2.5/weather?q="+city+"&appid=API_KEY";
        auto js_obj_2 = nlohmann::json::parse(get_request(link));
        return js_obj_2["weather.main"].get<float>()-273;// -273 in celcius
}
#endif
