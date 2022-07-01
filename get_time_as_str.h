#include <string>
#include <stdio.h>

using namespace std;

string get_time_as_str()
{
    time_t now = time(NULL);
    tm* ptr = localtime(&now);
    char buf[32];
    strftime(buf, 32, "%c", ptr);
    return buf;
}
