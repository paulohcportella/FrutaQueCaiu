
CC = gcc
CFLAGS = -Wall -Wextra -Icli-lib
LDFLAGS = -lncurses

SRC = main.c cli-lib/screen.c cli-lib/keyboard.c cli-lib/timer.c
TARGET = frutaquecaiu

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
