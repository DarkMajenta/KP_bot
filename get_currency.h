#include <stdio.h>
#include <string>
#include "get_request.h"
#include <nlohmann/json.hpp>

float get_currency(char what)
{
    auto js_obj = nlohmann::json::parse(get_request("https://www.cbr-xml-daily.ru/daily_json.js"));

    if (what=='u'){
        return js_obj["Valute"]["USD"]["Value"].get<float>();
    }
    else{
        return js_obj["Valute"]["KZT"]["Value"].get<float>();
    }
    return -1;
}

