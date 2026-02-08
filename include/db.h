#ifndef DB_H
#define DB_H

#include<sqlite3.h>
#include "weather.h"

void db_init(sqlite3 *db);
int save_weather(sqlite3 *db, const Weather *w);
int show_weather(sqlite3 *db);

#endif