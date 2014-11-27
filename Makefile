OBJS = CS14S015.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++0x $(DEBUG)
LFLAGS = -Wall $(DEBUG)

spell-check : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o spell-check

CS14S015.o : CS14S015.cpp
	$(CC) $(CFLAGS) CS14S015.cpp

clean:
	\rm *.o *~ spell-check

target:
	tar czfv CS14S015.tar.gz CS14S015.cpp Makefile
