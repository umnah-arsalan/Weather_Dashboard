#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char city[64];
    char api_key[128];
    char units[16];
} Config;

int load_config(const char *filename, Config *cfg);

#endif
