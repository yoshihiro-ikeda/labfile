include Makefile

BL_GRAPH_SRC  = BLGraph.cxx
BL_GRAPH_OBJ  = $(BL_GRAPH_SRC:.cxx=.o)
BL_GRAPH_PROG = $(BL_GRAPH_SRC:.cxx=)
BL_GRAPH_DEPS = $(BL_GRAPH_SRC:.cxx=.d)

BLG_CTRL_SRC  = blg_ctrl.cxx
BLG_CTRL_OBJ  = $(BLG_CTRL_SRC:.cxx=.o)
BLG_CTRL_PROG = $(BLG_CTRL_SRC:.cxx=)
BLG_CTRL_DEPS = $(BLG_CTRL_SRC:.cxx=.d)

BLG_TEST_SRC  = cpath_search_in_hierarchy.cxx
BLG_TEST_OBJ  = $(BLG_TEST_SRC:.cxx=.o)
BLG_TEST_PROG = $(BLG_TEST_SRC:.cxx=)
BLG_TEST_DEPS = $(BLG_TEST_SRC:.cxx=.d)

$(BL_GRAPH_OBJ): CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include/graphviz

GRAPHVIZ_LIB = -lcgraph -lcdt
GRAPHVIZ_ROOT = /usr

$(BLG_TEST_PROG): LDLIBS += $(BOOST_LIB) $(GRAPHVIZ_LIB)
$(BLG_TEST_PROG): $(BL_GRAPH_OBJ) $(BLG_CTRL_OBJ) $(LIBRARY)

PROGRAM += $(BLG_TEST_PROG)

all: $(BLG_TEST_PROG)

depend: $(BL_GRAPH_DEPS) $(BLG_CTRL_DEPS) $(BLG_TEST_DEPS)

-include $(BL_GRAPH_DEPS) $(BLG_CTRL_DEPS)
