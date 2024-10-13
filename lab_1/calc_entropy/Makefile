CC = gcc
CFLAGS = -Wall -Wextra -g -O1
LDFLAGS = -lm

SRCS = main.c calculateFREQ.c dict.c entropy.c read_buffer.c filter_text.c
OBJS = $(SRCS:.c=.o)
TARGET = text_analyzer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) #filter_text entropy_calculator
