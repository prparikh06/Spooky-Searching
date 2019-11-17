all:
	@echo Error: Please specify \'thread\' or \'proc\' targets. 	

proc: searchtest.c multitest_proc.o 
	gcc -fsanitize=address -std=c99 -o search searchtest.c multitest_proc.o -lm 

multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c

thread: searchtest.c multitest_thread.o
	gcc -fsanitize=address -std=c99 -o search searchtest.c multitest_thread.o -lm -lpthread

multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c

clean:
	rm -f search; rm *.o
