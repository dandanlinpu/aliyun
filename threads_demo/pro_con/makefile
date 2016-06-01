main:producer_consumer.o
	gcc -o main producer_consumer.o -pthread
producer_consumer.o: producer_consumer.c
	gcc -c producer_consumer.c
clean:
	rm -rf producer_consumer.o main
