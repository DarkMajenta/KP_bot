#include <stdio.h>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "get_request.h"

using namespace std;

float get_weather(string city)
{
        auto js_obj_2 = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?q="+city+"&appid="+API_KEY+"));
        return js_obj_2["weather.main"].get<float>();
}
