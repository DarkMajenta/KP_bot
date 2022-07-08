#ifndef WRITER_H
#define WRITER_H
#include <curl/curl.h>
#include <stdio.h>
#include <string>

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
}

#endif // WRITER_H
