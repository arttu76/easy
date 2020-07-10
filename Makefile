.DEFAULT_GOAL := watch

CC=gcc
CFLAGS=-Wall -lX11 -lm

template: template.c
	$(CC) $(CFLAGS) template.c easy.c -o template;

examples: examples/tunnel.c examples/interference.c examples/thrust2.c
	$(CC) $(CFLAGS) examples/tunnel.c easy.c -o tunnel;
	$(CC) $(CFLAGS) examples/interference.c easy.c -o interference;
	$(CC) $(CFLAGS) examples/thrust2.c easy.c -o thrust2;

clean:
	rm -f template tunnel interference thrust2

watch: clean ## continuously build and launch the file so you can concentrate on programming
	while true; do make template -q || ((killall template &) && make template && ./template &); sleep 1; done
