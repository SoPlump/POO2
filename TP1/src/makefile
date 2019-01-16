COMP = g++
COMPFLAGS = -ansi -pedantic -Wall -std=c++11
VALFLAGS = -g -O0
HEADER=$(wildcard *.h)
SOURCE=$(wildcard *.cpp)
OBJET=$(SOURCE:.cpp=.o)

ifdef MAP
	COMPFLAGS += -DMAP
endif

%.o : %.cpp %.h
	$(COMP) $(COMPFLAGS) $(DEFINES) -c $<

main : $(OBJET)
	$(COMP) -o main $(VALFLAGS) $(OBJET)
	
valgrind :
	valgrind --leak-check=yes ./main

clean :
	rm *.o main
