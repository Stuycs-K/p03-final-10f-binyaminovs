CC = gcc

CFLAGS = 

LDFLAGS = -lncurses

SRCS = edit.c

HEADERS = 

TARGET = edit

run: $(TARGET)
	@./$(TARGET)

compile: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o $(TARGET)

.PHONY: compile run clean

