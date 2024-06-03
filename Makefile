CC = gcc
CFLAGS = -Wall -Wextra
SRC = src/main.c src/user.c
INCLUDE = -Iinclude

all: login

login: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o login

clean:
	rm -f login
