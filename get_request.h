#ifndef GET_REQUEST_H
#define GET_REQUEST_H
#include <curl/curl.h>
#include "Writer.h"

using namespace std;

string get_request(string link)
{
    CURL *curl;
    string data;
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return data;
}
#endif
