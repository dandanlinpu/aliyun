main_pool:thpool.o example.o 
	gcc -o main_pool thpool.o example.o -pthread
thpool.o:thpool.c thpool.h
	gcc -c thpool.c 
example.o: example.c
	gcc -c example.c 
clean:
	rm -rf main_pool thpool.o example.o
