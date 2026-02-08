#include <stdio.h>
#include <string.h>
#include "config.h"

int load_config(const char *filename, Config *cfg) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char *key = line;
        char *value = eq + 1;

        value[strcspn(value, "\n")] = 0;

        if (strcmp(key, "city") == 0)
            strcpy(cfg->city, value);
        else if (strcmp(key, "api_key") == 0)
            strcpy(cfg->api_key, value);
        else if (strcmp(key, "units") == 0)
            strcpy(cfg->units, value);
    }

    fclose(fp);
    return 0;
}