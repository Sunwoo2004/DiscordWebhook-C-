#include "stdafx.h"
#define CURL_STATICLIB
#include <curl/curl.h>

using namespace std;

const char* webhook = "";

void SendData(const char* content)
{
    string szMsg = "content=```";
    szMsg += content;
    szMsg += "```";

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, webhook);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, szMsg.c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main()
{
    SendData("Test");
}