include Makefile

BL_GRAPH_SRC  = BLGraph.cxx
BL_GRAPH_OBJ  = $(BL_GRAPH_SRC:.cxx=.o)
BL_GRAPH_PROG = $(BL_GRAPH_SRC:.cxx=)
BL_GRAPH_DEPS = $(BL_GRAPH_SRC:.cxx=.d)

DFIHS_SRC  = dfihs.cxx
DFIHS_OBJ  = $(DFIHS_SRC:.cxx=.o)
DFIHS_PROG = $(DFIHS_SRC:.cxx=)
DFIHS_DEPS = $(DFIHS_SRC:.cxx=.d)

DFIHS_ALL_SRC = dfihsOptGraph.cxx dfihsDetermineNodePriority.cxx dfihsCreateTree.cxx dfihsSetCoreinfo.cxx dfihsForMultirate.cxx
DFIHS_ALL_OBJ  = $(DFIHS_ALL_SRC:.cxx=.o)
DFIHS_ALL_PROG = $(DFIHS_ALL_SRC:.cxx=)
DFIHS_ALL_DEPS = $(DFIHS_ALL_SRC:.cxx=.d)

GRAPHVIZ_LIB = -lcgraph -lcdt
GRAPHVIZ_ROOT = /usr
$(BL_GRAPH_OBJ): CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include/graphviz

$(DFIHS_PROG): LDLIBS += $(BOOST_LIB) $(GRAPHVIZ_LIB)
$(DFIHS_PROG): $(BL_GRAPH_OBJ) $(DFIHS_ALL_OBJ) $(LIBRARY)
$(DFIHS_PROG): dfihs.hxx

PROGRAM += $(DFIHS_PROG)

all: $(DFIHS_PROG)

depend: $(BL_GRAPH_DEPS) $(DFIHS_DEPS) $(DFIHS_ALL_DEPS)

-include $(BL_GRAPH_DEPS)
