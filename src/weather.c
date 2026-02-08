#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "weather.h"
#include "config.h"

typedef struct {
    char *data;
    size_t size;
} Buffer;

static size_t write_cb(void *ptr, size_t size, size_t nmemb, void *userdata) {
    Buffer *buf = userdata;
    size_t total = size * nmemb;

    buf->data = realloc(buf->data, buf->size + total + 1);
    memcpy(buf->data + buf->size, ptr, total);
    buf->size += total;
    buf->data[buf->size] = '\0';

    return total;
}

int fetch_weather(const Config *cfg, Weather *w) {
    CURL *curl = curl_easy_init();
    if (!curl) return -1;

    char url[512];
    snprintf(url, sizeof(url),
        "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=%s",
        cfg->city, cfg->api_key, cfg->units);

    Buffer buf = {0};

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);

    if (curl_easy_perform(curl) != CURLE_OK) {
        curl_easy_cleanup(curl);
        return -1;
    }

    cJSON *json = cJSON_Parse(buf.data);
    cJSON *main = cJSON_GetObjectItem(json, "main");
    cJSON *weather = cJSON_GetArrayItem(
        cJSON_GetObjectItem(json, "weather"), 0);

    w->temp = cJSON_GetObjectItem(main, "temp")->valuedouble;
    w->humidity = cJSON_GetObjectItem(main, "humidity")->valueint;
    strcpy(w->description, cJSON_GetObjectItem(weather, "description")->valuestring);

    printf("Inserted!\n");

    cJSON_Delete(json);
    free(buf.data);
    curl_easy_cleanup(curl);
    return 0;
}
