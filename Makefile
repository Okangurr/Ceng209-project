CC = gcc
CFLAGS = -Wall -g
TARGET = advanture_game
SRCS = Advanture_game.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe
