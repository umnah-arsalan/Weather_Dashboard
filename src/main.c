#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "config.h"
#include "weather.h"
#include "db.h"
#include "log.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s fetch|show\n", argv[0]);
        return 1;
    }

    sqlite3 *db;
    Config cfg;
    Weather w;

    if (sqlite3_open("data/weather.db", &db) != SQLITE_OK)
        return -1;

    load_config("config.ini", &cfg);
    db_init(db);

    if (strcmp(argv[1], "fetch") == 0) {
        fetch_weather(&cfg, &w);
        save_weather(db, &w);
        log_message("Weather fetched");
    }
    else if (strcmp(argv[1], "show") == 0) {
        show_weather(db);
    }

    sqlite3_close(db);
    return 0;
}