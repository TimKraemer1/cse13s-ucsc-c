EXEC = encode
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
LDFLAGS = -lm
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tidy:
	rm -rf $(OBJECTS)

clean: tidy
	rm -rf $(EXEC)

format:
	clang-format -i -style=file *.c *.h
