#pragma once

#include <curl/curl.h>
#include <string>
#include <regex>
#include <curl/curl.h>
#include "Constants.hpp"

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

//list of private ip addresses taken from 
//https://en.wikipedia.org/wiki/Private_network
static bool isPrivateIPAddress(std::string ip)
{    
    return (std::regex_search(ip, std::regex(TCPDP_REGEX::PRIVATE_IP, std::regex_constants::ECMAScript)));
}

static std::string locationFromIP(std::string ip)
{
    if (isPrivateIPAddress(ip))
        return TCPDP_NETWORK::PRIVATE_IP_LABEL;
    std::string url = TCPDP_NETWORK::IP_LOCATION_BASE_URL + ip;
    std::string readBuffer;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    int subIndex;
    std::string location = readBuffer;
    if ((subIndex = readBuffer.find_last_of(";")) != std::string::npos)
        location = readBuffer.substr(subIndex+1);
    return location;
}