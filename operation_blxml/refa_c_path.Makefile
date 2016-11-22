include Makefile

BL_GRAPH_SRC  = BLGraph.cxx
BL_GRAPH_OBJ  = $(BL_GRAPH_SRC:.cxx=.o)
BL_GRAPH_PROG = $(BL_GRAPH_SRC:.cxx=)
BL_GRAPH_DEPS = $(BL_GRAPH_SRC:.cxx=.d)

BLG_TEST_SRC  = refa_c_path.cxx
BLG_TEST_OBJ  = $(BLG_TEST_SRC:.cxx=.o)
BLG_TEST_PROG = $(BLG_TEST_SRC:.cxx=)
BLG_TEST_DEPS = $(BLG_TEST_SRC:.cxx=.d)

#Simulink_XSDのバージョンによって以下の記述いらないかも

GRAPHVIZ_LIB = -lcgraph -lcdt
GRAPHVIZ_ROOT = /usr

$(BL_GRAPH_OBJ): CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include/graphviz

$(BLG_TEST_PROG): LDLIBS += $(BOOST_LIB) $(GRAPHVIZ_LIB)
$(BLG_TEST_PROG): $(BL_GRAPH_OBJ) $(LIBRARY)

PROGRAM += $(BLG_TEST_PROG)

all: $(BLG_TEST_PROG)

depend: $(BL_GRAPH_DEPS) $(BLG_TEST_DEPS)

clean: refa_c_path
	rm refa_c_path

-include $(BL_GRAPH_DEPS)
