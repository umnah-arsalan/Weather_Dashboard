#include <stdio.h>
#include <sqlite3.h>
#include "db.h"
#include "weather.h"

void db_init(sqlite3 *db) {
    char *err = NULL; 
    const char *sql =
        "CREATE TABLE IF NOT EXISTS weather ("
        "temp REAL,"
        "humidity INTEGER,"
        "description TEXT);";
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("Error creating table: %s\n", err);
        sqlite3_free(err);
    }
}

int save_weather(sqlite3 *db, const Weather *w) {
    const char *sql =
        "INSERT INTO weather (temp, humidity, description) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("Prepare failed: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_double(stmt, 1, w->temp);
    sqlite3_bind_int(stmt, 2, w->humidity);
    sqlite3_bind_text(stmt, 3, w->description, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Insert failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int show_weather(sqlite3 *db) {
    const char *sql = "SELECT * FROM weather ORDER BY description DESC LIMIT 1;";
    sqlite3_stmt *stmt;

    printf("Querying database...\n");

    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\n🌤 Weather Dashboard\n");
        printf("Temp: %.2f°C\n", sqlite3_column_double(stmt, 0));
        printf("Humidity: %d%%\n", sqlite3_column_int(stmt, 1));
        printf("Status: %s\n", sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
    return 0;
}