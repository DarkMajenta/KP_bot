#include <stdio.h>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "get_request.h"

using namespace std;

float get_weather(string city)
{
    auto js_obj = nlohmann::json::parse("./city.list.json");
    while(js_obj["name"].get<string>() != city){
    if(js_obj["name"].get<string>() == city){
        float lon,lat;
        lon = js_obj["coord.lon"].get<float>();
        lat = js_obj["coord.lat"].get<float>();
        auto js_obj_2 = nlohmann::json::parse(get_request("https://api.openweathermap.org/data/2.5/weather?lat={"+lat+"}&lon={"+lon+"}&appid={}"));
        return js_obj_2["weather.main"].get<float>();
        break;
    }
    };
}
