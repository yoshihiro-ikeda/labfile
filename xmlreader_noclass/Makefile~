CC = g++
CPPFLAGS += -std=c99 -pedantic

OBJ = $(SRC:.cxx=.o)
PROG = $(SRC:.cxx=)
LDLIBS += -lxerces-c
LDLIBS += -lboost_regex
LDLIBS += libSimulinkXSD.a
all: 
	$(CC) -o $(PROG) $(SRC) $(LDLIBS)

