.PHONY: all clean debug

all: fifo_to_complete debug

debug: fifo_to_complete_debug

fifo_to_complete_debug: fifo_to_complete.c
	gcc -g -ggdb -Wall -Werror -Wextra -pedantic fifo_to_complete.c -o fifo_to_complete_debug

fifo_to_complete: fifo_to_complete.c
	gcc fifo_to_complete.c -o fifo_to_complete

clean:
	rm fifo_to_complete fifo_to_complete_debug