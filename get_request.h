#include <stdio.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <curl/curl.h>

using namespace std;

static char errrorBuffer[CURL_ERROR_SIZE];
static string buffer;

static int Writer(char *buffer, size_t size, size_t nmemb, string *html)
{
    int result=0;

    if (buffer != NULL)
    {
        html -> append(buffer, size*nmemb);
        result = size*nmemb;
    }
    return result;
}

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
