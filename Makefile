CC = gcc
CFLAGS = -Wall -Iincludes
LDFLAGS = -lsqlite3
SRC = src/main.c src/auth.c src/database.c src/country.c src/region.c
OBJ = $(SRC:.c=.o)
EXEC = bin/countryapp.exe

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    del $(OBJ) $(EXEC)

.PHONY: all clean