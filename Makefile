NAME = manalink

CXXFLAGS = -Wall

LFLAGS = -lncurses

SOURCES = main.cpp\
	Category.cpp\
	SaveManager.cpp

OBJS = $(SOURCES:.cpp=.o)

CC = g++

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f *.o *~ $(NAME)

re: clean all
