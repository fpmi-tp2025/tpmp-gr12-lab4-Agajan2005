CC = gcc
CFLAGS = -Wall -Iincludes
LDFLAGS = -lsqlite3

TARGET = bin/country_app
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = includes

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/auth.c $(SRC_DIR)/database.c $(SRC_DIR)/country.c $(SRC_DIR)/region.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
