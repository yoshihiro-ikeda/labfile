include Makefile

BL_GRAPH_SRC  = BLGraph.cxx
BL_GRAPH_OBJ  = $(BL_GRAPH_SRC:.cxx=.o)
BL_GRAPH_PROG = $(BL_GRAPH_SRC:.cxx=)
BL_GRAPH_DEPS = $(BL_GRAPH_SRC:.cxx=.d)

BLTMP2_SRC  = bltmp2c.cxx
BLTMP2_OBJ  = $(BLTMP2_SRC:.cxx=.o)
BLTMP2_PROG = $(BLTMP2_SRC:.cxx=)
BLTMP2_DEPS = $(BLTMP2_SRC:.cxx=.d)

BLTMP2_9_SRC  = bltmp2c_0_graph.cxx bltmp2c_0_rate.cxx bltmp2c_1.cxx \
	bltmp2c_2.cxx bltmp2c_3.cxx bltmp2c_8.cxx bltmp2c_9.cxx bltmp2c_util.cxx
BLTMP2_9_OBJ  = $(BLTMP2_9_SRC:.cxx=.o)
BLTMP2_9_PROG = $(BLTMP2_9_SRC:.cxx=)
BLTMP2_9_DEPS = $(BLTMP2_9_SRC:.cxx=.d)

$(BL_GRAPH_OBJ): CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include/graphviz

$(BLTMP2_PROG): LDLIBS += $(BOOST_LIB) $(GRAPHVIZ_LIB)
$(BLTMP2_PROG): $(BL_GRAPH_OBJ) $(BLTMP2_9_OBJ) $(LIBRARY)

PROGRAM += $(BLTMP2_PROG)

all: $(BLTMP2_PROG)

depend: $(BL_GRAPH_DEPS) $(BLTMP2_9_DEPS) $(BLTMP2_DEPS)

-include $(BL_GRAPH_DEPS)
