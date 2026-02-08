#include <stdio.h>
#include <time.h>
#include "log.h"

void log_message(const char *msg) {
    FILE *fp = fopen("weathercli.log", "a");
    time_t now = time(NULL);
    fprintf(fp, "%s: %s\n", ctime(&now), msg);
    fclose(fp);
}