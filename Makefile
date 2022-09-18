CC = g++
CFLAGS = -g -Wall -Werror -O2
WORKSRC = decipher.cpp bigint.cpp
WORKOBJ = $(WORKSRC:.cpp=.o)

all: $(WORKOBJ)
	$(CC) $(CFLAGS) $(WORKOBJ) -o decipher

bigint.o: bigint.cpp bigint.h
	$(CC) $(CFLAGS) -c $< -o $@

test: bigint.o test.cpp
	$(CC) $(CFLAGS) $^ -o $@
	
mytest: bigint.o mytest.cpp
	$(CC) $(CFLAGS) $^ -o $@

constructor_test: bigint.o constructor_test.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o test decipher mytest constructor_test


