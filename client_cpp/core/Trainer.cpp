
#include "Trainer.hpp"

#include <unistd.h>

Trainer::Trainer(Args &a, IInterface *i) :
    _a(a),
    _i(i)

{
    _i->prompt("Welcome");
}

Trainer::~Trainer() {}


#include <curl/curl.h>
#define SERVER_URL "http://localhost::7575"
#include <iostream>
std::string data; //will hold the url's contents

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{
    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

int     Trainer::getNextTestId()
{
    CURL               *curl = curl_easy_init();
    struct curl_slist  *headers = NULL;
    int                 id;
    int                 res;
    // Headers
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Opts
    curl_easy_setopt(curl, CURLOPT_URL, SERVER_URL"/getnextid");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Run
    res = curl_easy_perform(curl);
    // TODO: More specifique message
    if (res != CURLE_OK)
        std::cerr << "CURL ERROR" << std::endl;
    else
        std::cout << data << std::endl;
    // Clean
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return id;
}

// TODO: ca na rien a voir avec le trainer
Test    *Trainer::getTest(int id)
{
    Test *t = new Test();
    return (t);
}

void    Trainer::test(Test *t)
{
}

int     Trainer::run(void) {
    bool cte = true;
    int  ret = 0;
    Test    *t;

    while (cte)
    {
        int testId = this->getNextTestId();
        t = this->getTest(testId);
        this->test(t);
        t->uploadRes();
        delete t;
    }
    return ret;
}

/*
    CURL *curl = curl_easy_init();
    int postsize = 0;
    {
        struct curl_slist *headers = NULL;
        {
            std::stringstream   ss;

            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, "http://bbfs.seed-up.org/data");
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            ss << "{\"logs\": [";
            auto ite = result.end();
            for (auto it = result.begin(); it != ite; ++it)
            {
                t_logs  logs = *it;
                ss << "{"
                    << "\"path\":\"" << logs.path << "\","
                    << "\"inode\":\"" << logs.inode << "\","
                    << "\"user_name\":\"" << logs.user_name << "\","
                    << "\"mac\":\"" << logs.mac << "\","
                    << "\"action\":\"" << logs.action << "\","
                    << "\"timestamp\":\"" << logs.timestamp << "\""
                    << (it + 1 != ite ? "}," : "}");
            }
            ss << "]}";
            std::string json = ss.str();
            postsize = json.length();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postsize);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
            int res = curl_easy_perform(curl);
            int http_code = 0;

            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (res != CURLE_OK)
                postsize = -1, dprintf(2, "%s:%d: ERROR with curl\n", __FILE__, __LINE__);
            else if (http_code >= 400)
                postsize = -2, dprintf(2, "%s:%d: ERROR http code: %d\n", __FILE__, __LINE__, http_code);
            else
                (void)1; // TODO: Data is sended so set uploadted to 1
        }
        curl_slist_free_all(headers);
    }
    curl_easy_cleanup(curl);
 *int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  return 0;
}
 * */
