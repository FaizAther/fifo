fifo_to_complete: fifo_to_complete.c
	gcc -g -ggdb -Wall -Werror -Wextra fifo_to_complete.c -o fifo_to_complete

clean:
	rm fifo_to_complete