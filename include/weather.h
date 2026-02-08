#ifndef WEATHER_H
#define WEATHER_H

#include "config.h"

typedef struct {
    double temp;
    int humidity;
    char description[64];
} Weather;

int fetch_weather(const Config *cfg, Weather *w);

#endif