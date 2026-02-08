CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=-lcurl -lcjson -lsqlite3
INCLUDES = -Iinclude

SRC=src/main.c src/config.c src/weather.c src/db.c src/log.c
OBJ=$(SRC:src/%.c=build/%.o)

weathercli: $(OBJ)
	$(CC) $(OBJ) -o weathercli $(LIBS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build weathercli
