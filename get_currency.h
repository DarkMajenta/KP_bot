#ifndef GET_CURRENCY_H
#define GET_CURRENCY_H
#include "get_request.h"
#include <nlohmann/json.hpp>
#include <stdio.h>

using namespace std;

float get_currency(char what)
{
    auto js_obj = nlohmann::json::parse(get_request("https://www.cbr-xml-daily.ru/daily_json.js"));

    if (what=='u'){
        return js_obj["Valute"]["USD"]["Value"].get<float>();
    }
    if (what == 'k') {
        return js_obj["Valute"]["KZT"]["Value"].get<float>();
    }
    return -1;
}
#endif
