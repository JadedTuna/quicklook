CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags --libs gtk+-3.0`
NAME = quicklook

all:
	$(CC) src/$(NAME).c $(CFLAGS) -o $(NAME)
