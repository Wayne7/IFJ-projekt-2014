NAME=interpret
FILES=main.c garbage_collector.c strings.c scanner.c parser.c ial.c
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic  -lm

$(NAME): $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $@

