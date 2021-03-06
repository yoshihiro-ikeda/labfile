DISTRIB = n
USE_DMALLOC = n
SIMULINK_URL = http://example.com/SimulinkModel	# name space (XML schema)

SHIM = SHIM.xml

# enable gdb debug (no optimization)
LLVM_PASS_DEBUG = n

# enable debug message
LLVM_DEBUG = n

# output loop graph for debug
LLVM_LOOP_GRAPH_DEBUG = n

XSD_OPT = -O2

CXX = g++
DOT = dot

CXXFLAGS += -Wall
CXXFLAGS += -g

LDFLAGS += -g

LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

LIBRARY = libSimulinkXSD.a
LIBRARY_OBJS =

# if your Xerces-C++ is installed alternate path, you change it.
# PKG_CONFIG = PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config
PKG_CONFIG = pkg-config

LLVM_CONFIG = llvm-config

OS := $(shell uname -s)

M4 = m4
GNU_M4 := $(strip $(shell echo "ifdef(\`__gnu__',\`y',\`n')" | $(M4)))

XSDCXX := $(strip $(shell if type xsdcxx 1>/dev/null 2>&1; then echo y; else echo n; fi))

ifneq ($(DISTRIB),y)
DISTRIB := $(strip $(shell test -f $(SIMULINK_XML_SCHEMA_M4) || echo y))
endif

IS_MINGW=n
ifeq ($(OS),MINGW32_NT-6.1)
IS_MINGW=32
else
ifeq ($(OS),MINGW64_NT-6.1)
IS_MINGW=64
endif
endif

ifneq ($(IS_MINGW),n)
PKG_CONFIG := ./mingw_correct.sh $(PKG_CONFIG)
LLVM_CONFIG := ./mingw_correct.sh $(LLVM_CONFIG)
DLL_EXT=.dll
EXE_EXT=.exe
PIC_OPTION=
else
BOOSTLIB_EXT=
DLL_EXT=.so
EXE_EXT=
PIC_OPTION=-fPIC
endif

XERCES_LIBS := $(shell $(PKG_CONFIG) --libs xerces-c)
XERCES_CFLAGS := $(shell $(PKG_CONFIG) --cflags xerces-c)
XERCES_ROOT := $(shell $(PKG_CONFIG) --variable=prefix xerces-c)
XERCES_LIBDIR := $(shell $(PKG_CONFIG) --variable=libdir xerces-c)

ifneq ($(DISTRIB),y)
LLVM_VERSION := $(shell $(LLVM_CONFIG) --version)
LLVM_BINDIR := $(shell $(LLVM_CONFIG) --bindir)
LLVM_LIBDIR := $(shell $(LLVM_CONFIG) --libdir)
LLVM_LIBS := $(shell $(LLVM_CONFIG) --libs)
LLVM_CPPFLAGS := $(shell $(LLVM_CONFIG) --cppflags)
LLVM_CFLAGS := $(shell $(LLVM_CONFIG) --cflags)
LLVM_CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags)
LLVM_SYSTEM_LIBS := $(shell $(LLVM_CONFIG) --system-libs 2>/dev/null)

FILTER_DISABLE_CXX = -fno-exceptions -fno-rtti
FILTER_NOOPT = -O -O1 -O2 -O3 -Wp,-D_FORTIFY_SOURCE=2
LLVM_NOOPT_CXXFLAGS = $(filter-out $(FILTER_NOOPT), $(LLVM_CXXFLAGS))
LLVM_NOOPT_CFLAGS = $(filter-out $(FILTER_NOOPT), $(LLVM_CFLAGS))
endif

LLVM_OTHER_CXXFLAGS = $(filter-out $(FILTER_DISABLE_CXX), $(LLVM_CXXFLAGS))

ifeq ($(DLL_EXT),.so)
LLVM_SHARED_LIB = $(LLVM_LIBDIR)/libLLVM-$(LLVM_VERSION).so
LLVM_SHARED_LIB_OPT = -lLLVM-$(LLVM_VERSION)
else
LLVM_SHARED_LIB = $(LLVM_BINDIR)/LLVM-$(LLVM_VERSION).dll
LLVM_SHARED_LIB_OPT = $(LLVM_SHARED_LIB)
endif

ifneq ($(shell test -f $(LLVM_SHARED_LIB) || echo n),n)
LLVM_LIBS := $(LLVM_SHARED_LIB_OPT)
endif

BOOST_LIB = -lboost_regex$(BOOSTLIB_EXT)

GRAPHVIZ_LIB = -lcgraph -lcdt

GRAPHVIZ_ROOT = /usr

# prior path for libraries
ifeq ($(OS),SunOS)
ifeq ($(notdir $(CXX)),g++)
GXX_LIBSTDCXX_PATH := $(shell $(CXX) -print-file-name=libstdc++.so)
GCC_LIBDIR := $(realpath $(dir $(GXX_LIBSTDCXX_PATH)))
# contributed standard install path
ifneq ($(GCC_LIBDIR),/usr/local/lib)
ifneq ($(GCC_LIBDIR),/usr/local/lib/amd64)
LDFLAGS += -L$(GCC_LIBDIR) -R$(GCC_LIBDIR)
endif
endif
endif
LLVM_LDFLAGS += -R$(LLVM_LIBDIR)
endif

LDLIBS += $(XERCES_LIBS)

# Solaris
ifeq ($(OS),SunOS)
#XSD_ROOT = /usr/local/xsd-3.3.0-i686-solaris
XSD_ROOT = /usr/local/xsd-4.0.0-i686-solaris
XSD = $(XSD_ROOT)/bin/xsd
CPPFLAGS += -I$(XSD_ROOT)/libxsd
LDFLAGS += -R$(XERCES_LIBDIR)
LDLIBS += -liconv
endif

# Linux
ifeq ($(OS),Linux)
ifeq ($(XSDCXX),y)
XSD = xsdcxx
else
XSD = xsd
endif
endif

# CYGWIN
ifeq ($(OS),CYGWIN_NT-6.1)
XSD_ROOT = /cygdrive/C/ICF_AutoCapsule_disabled/xsd-4.0.0-i686-windows
GRAPHVIZ_ROOT = /usr/local

XSD = $(XSD_ROOT)/bin/xsd.exe
BOOST_LIB = -lboost_regex

CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include
CPPFLAGS += -I$(XSD_ROOT)/libxsd

LDFLAGS += -L$(GRAPHVIZ_ROOT)/lib

ifneq ($(GRAPHVIZ_ROOT),$(XERCES_ROOT))
CPPFLAGS += -I$(XERCES_ROOT)/include
LDFLAGS += -L$(XERCES_ROOT)/lib
endif

endif

ifneq ($(IS_MINGW),n)
include mingw.conf.mk
CPPFLAGS += -I$(MINGW_BOOST_INCLUDE_DIR)
CPPFLAGS += -I$(MINGW_MMAN_INCLUDE_DIR)
CPPFLAGS += -I$(MINGW_GRAPHVIZ_INCLUDE_DIR)
CPPFLAGS += -idirafter $(MINGW_XSD_INCLUDE_DIR)
LDFLAGS += -L$(MINGW_BOOST_LIB_DIR)
LDFLAGS += -L$(MINGW_GRAPHVIZ_LIB_DIR)
LDFLAGS += -L$(MINGW_MMAN_LIB_DIR)
LDLIBS += -lmman
BOOSTLIB_EXT = $(MINGW_BOOST_LIB_EXT)
XSD = $(MINGW_XSD_COMMAND)
endif

ifneq ($(GRAPHVIZ_ROOT),/usr/local)
ifneq ($(XERCES_ROOT),/usr/local)
CPPFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib
endif
endif

ifeq ($(USE_DMALLOC),y)
CPPFLAGS += -DUSE_DMALLOC
LDLIBS += -ldmallocxx
endif

ifeq ($(LLVM_DEBUG),y)
CPPFLAGS += -DLLVM_DEBUG
endif

CPPFLAGS += $(XERCES_CFLAGS)

TEST_SIMULINK_TARGET_OUT = 
TEST_BLXML_TARGET_OPTION_ADD =

include test.conf.mk

TEST_RTW_FILE_OPTIONS = -c $(TEST_RTW_TARGET_SRC) -h $(TEST_RTW_TARGET_HDR)
ifneq ($(TEST_RTW_TARGET_DAT),none)
TEST_RTW_FILE_OPTIONS += -d $(TEST_RTW_TARGET_DAT)
endif

TEST_DOT_TARGET_OUT = $(dir $(TEST_RTW_TARGET_OUT))test_xml.dot
TEST_PNG_TARGET_OUT = $(TEST_DOT_TARGET_OUT:.dot=.png)

TEST_RTW_TARGET_LOG = $(dir $(TEST_RTW_TARGET_OUT))test_rtw.log
TEST_SIMULINK_TARGET_LOG = $(dir $(TEST_RTW_TARGET_OUT))test_sim.log
TEST_XML_TARGET_LOG = $(dir $(TEST_RTW_TARGET_OUT))test_xml.log

TEST_BLXML_TARGET_DIR = $(dir $(TEST_RTW_TARGET_OUT))
TEST_BLXML_TARGET_OUT = $(TEST_BLXML_TARGET_DIR)test_blxml.xml
TEST_BLXML_TARGET_INCLUDE = -I$(dir $(TEST_RTW_TARGET_SRC))
TEST_BLXML_TARGET_DOT_BASE = $(TEST_BLXML_TARGET_OUT:.xml=)

TEST_BLXML_TARGET_OPTIONS = -C -O -shim=$(SHIM) -shim-schema=$(SHIM_XSD)
ifeq ($(LLVM_LOOP_GRAPH_DEBUG),y)
TEST_BLXML_TARGET_OPTIONS += -O -out-dot=$(TEST_BLXML_TARGET_DOT_BASE)
endif
ifneq ($(IS_MINGW),n)
TEST_BLXML_TARGET_OPTION_ADD += -C -I/mingw/include
endif
TEST_BLXML_TARGET_OPTIONS += $(TEST_BLXML_TARGET_OPTION_ADD)

# sizing
CXXFLAGS += -ffunction-sections -fdata-sections

XSD_OPTIONS += --generate-serialization
XSD_OPTIONS += --generate-doxygen
XSD_OPTIONS += --char-encoding utf8

.SUFFIXES : .cxx .hxx .xsd .xml .m4 $(DLL_EXT)
SUFFIXES := $(SUFFIXES) .cxx .hxx .xsd .xml .m4 $(DLL_EXT)

SIMULINK_DRIVER_SRC = xsd_driver.cxx
SIMULINK_DRIVER_OBJ = $(SIMULINK_DRIVER_SRC:.cxx=.o)
SIMULINK_DRIVER_PROG = $(SIMULINK_DRIVER_SRC:.cxx=)
SIMULINK_DRIVER_PROGFILE = $(SIMULINK_DRIVER_SRC:.cxx=$(EXE_EXT))
SIMULINK_DRIVER_DEPS = $(SIMULINK_DRIVER_SRC:.cxx=.d)

SIMULINK_NAMESPACE = SimulinkModel::XSD		# namespace (do not change)
SIMULINK_XML_SCHEMA = SimulinkModel.xsd
SIMULINK_XML_SCHEMA_M4 = $(SIMULINK_XML_SCHEMA:.xsd=.m4)
SIMULINK_XSD_SRC = $(SIMULINK_XML_SCHEMA:.xsd=.cxx)
SIMULINK_XSD_HDR = $(SIMULINK_XML_SCHEMA:.xsd=.hxx)
SIMULINK_XSD_OBJ = $(SIMULINK_XML_SCHEMA:.xsd=.o)
SIMULINK_XSD_DEPS = $(SIMULINK_XML_SCHEMA:.xsd=.d)
SIMULINK_DOXYGEN = SimulinkModel.doxygen
SIMULINK_XML_NS_HDR = SimulinkModel_ns.h

SIMULINK_XSD_OPTIONS += --root-element blocks

XSD_SRCS = $(SIMULINK_XSD_SRC)
XSD_FILES = $(SIMULINK_XSD_SRC) $(SIMULINK_XSD_HDR)

XSD_OBJS = $(XSD_SRCS:.cxx=.o)

RTW_TEST_SRC = rtw_test.cxx
RTW_TEST_OBJ = $(RTW_TEST_SRC:.cxx=.o)
RTW_TEST_PROG = $(RTW_TEST_SRC:.cxx=)
RTW_TEST_PROGFILE = $(RTW_TEST_SRC:.cxx=$(EXE_EXT))
RTW_TEST_DEPS = $(RTW_TEST_SRC:.cxx=.d)

RTW_SRCS = SimulinkRTW.cxx
RTW_HDRS = SimulinkRTW.h
RTW_OBJS = $(RTW_SRCS:.cxx=.o)
RTW_DEPS = $(RTW_SRCS:.cxx=.d)

XML_TEST_SRC = xml_test.cxx
XML_TEST_OBJ = $(XML_TEST_SRC:.cxx=.o)
XML_TEST_PROG = $(XML_TEST_SRC:.cxx=)
XML_TEST_PROGFILE = $(XML_TEST_SRC:.cxx=$(EXE_EXT))
XML_TEST_DEPS = $(XML_TEST_SRC:.cxx=.d)

BLXML2CODE_SRC = blxml2code.cxx
BLXML2CODE_OBJ = $(BLXML2CODE_SRC:.cxx=.o)
BLXML2CODE_PROG = $(BLXML2CODE_SRC:.cxx=)
BLXML2CODE_PROGFILE = $(BLXML2CODE_SRC:.cxx=$(EXE_EXT))
BLXML2CODE_DEPS = $(BLXML2CODE_SRC:.cxx=.d)

ADD_BLOCK_INFO_SRC = add_block_info.cxx
ADD_BLOCK_INFO_OBJ = $(ADD_BLOCK_INFO_SRC:.cxx=.o)
ADD_BLOCK_INFO_PROG = $(ADD_BLOCK_INFO_SRC:.cxx=)
ADD_BLOCK_INFO_PROGFILE = $(ADD_BLOCK_INFO_SRC:.cxx=$(EXE_EXT))
ADD_BLOCK_INFO_DEPS = $(ADD_BLOCK_INFO_SRC:.cxx=.d)

DUMP_BLOCK_LIST_SRC = dump_block_list.cxx
DUMP_BLOCK_LIST_OBJ = $(DUMP_BLOCK_LIST_SRC:.cxx=.o)
DUMP_BLOCK_LIST_PROG = $(DUMP_BLOCK_LIST_SRC:.cxx=)
DUMP_BLOCK_LIST_PROGFILE = $(DUMP_BLOCK_LIST_SRC:.cxx=$(EXE_EXT))
DUMP_BLOCK_LIST_DEPS = $(DUMP_BLOCK_LIST_SRC:.cxx=.d)

XML_SRCS = SimulinkXML.cxx
XML_HDRS = SimulinkXML.h
XML_OBJS = $(XML_SRCS:.cxx=.o)
XML_DEPS = $(XML_SRCS:.cxx=.d)

#SHIM_XSD_VERSION=20140414
#SHIM_XSD_VERSION=20140908
#SHIM_XSD_VERSION=20140924
SHIM_XSD_VERSION=20150212
SHIM_XSD = shim.xsd
SHIM_XSD_SRCS = $(SHIM_XSD:.xsd=.cxx)
SHIM_XSD_HDRS = $(SHIM_XSD:.xsd=.hxx)
SHIM_XSD_OPTIONS += --namespace-map =SHIM --root-element SystemConfiguration
SHIM_XSD_OBJS = $(SHIM_XSD_SRCS:.cxx=.o)
SHIM_XSD_DEPS = $(SHIM_XSD_SRCS:.cxx=.d)

LLVM_PASS_SRCS = llvm-BLXMLPerf.cxx
LLVM_PASS_HDRS = llvm-BLXMLPerf.h
LLVM_PASS_OBJS = $(LLVM_PASS_SRCS:.cxx=.o)
LLVM_PASS_SHLIB = $(LLVM_PASS_SRCS:.cxx=$(DLL_EXT))
LLVM_PASS_DEPS = $(LLVM_PASS_SRCS:.cxx=.d)

SHIM_LLVM_SRCS = shim_llvm.cxx
SHIM_LLVM_HDRS = shim_llvm.h
SHIM_LLVM_OBJS = $(SHIM_LLVM_SRCS:.cxx=.o)
SHIM_LLVM_DEPS = $(SHIM_LLVM_SRCS:.cxx=.d)

BLXML_LLVM_SRCS = blxml_llvm.cxx
BLXML_LLVM_HDRS = blxml_llvm.h
BLXML_LLVM_OBJS = $(BLXML_LLVM_SRCS:.cxx=.o)
BLXML_LLVM_DEPS = $(BLXML_LLVM_SRCS:.cxx=.d)

BOOST_LLVM_SRCS = boost_llvm.cxx
BOOST_LLVM_HDRS = boost_llvm.h
BOOST_LLVM_OBJS = $(BOOST_LLVM_SRCS:.cxx=.o)
BOOST_LLVM_DEPS = $(BOOST_LLVM_SRCS:.cxx=.d)

LLVM_PASS_SUB_SRCS = $(SHIM_XSD_SRCS) $(SHIM_LLVM_SRCS) $(BLXML_LLVM_SRCS) \
		     $(BOOST_LLVM_SRCS)
LLVM_PASS_SUB_HDRS = $(SHIM_XSD_HDRS) $(SHIM_LLVM_HDRS) $(BLXML_LLVM_HDRS) \
		     $(BOOST_LLVM_HDRS)
LLVM_PASS_SUB_OBJS = $(SHIM_XSD_OBJS) $(SHIM_LLVM_OBJS) $(BLXML_LLVM_OBJS) \
		     $(BOOST_LLVM_OBJS)
LLVM_PASS_SUB_DEPS = $(SHIM_XSD_DEPS) $(SHIM_LLVM_DEPS) $(BLXML_LLVM_DEPS) \
		     $(BOOST_LLVM_DEPS)

ifdef SIMULINK_NAMESPACE
SIMULINK_XSD_OPTIONS += --namespace-map $(strip $(SIMULINK_URL))=$(strip $(SIMULINK_NAMESPACE))
endif

LIBRARY_OBJS += $(XSD_OBJS) $(XML_OBJS)

ARCHIVE_MEMBER = $(patsubst %,$(LIBRARY)(%),$(LIBRARY_OBJS))

ifeq ($(DISTRIB),y)
ALL_DEPS = $(SIMULINK_XSD_DEPS) $(RTW_DEPS) $(XML_DEPS) $(RTW_TEST_DEPS)
PROGRAM = $(RTW_TEST_PROG) $(XML_TEST_PROG)
PROGRAM_FILES = $(RTW_TEST_PROGFILE) $(XML_TEST_PROGFILE)
else
ALL_DEPS = $(SIMULINK_XSD_DEPS) $(RTW_DEPS) $(XML_DEPS) \
	$(SIMULINK_DRIVER_DEPS) $(RTW_TEST_DEPS) $(XML_TEST_DEPS) \
	$(BLXML2CODE_DEPS) $(LLVM_PASS_DEPS) $(LLVM_PASS_SUB_DEPS) \
	$(ADD_BLOCK_INFO_DEPS) $(DUMP_BLOCK_LIST_DEPS)
PROGRAM = $(SIMULINK_DRIVER_PROG) $(RTW_TEST_PROG) $(XML_TEST_PROG) \
	$(BLXML2CODE_PROG) $(LLVM_PASS_SHLIB) $(ADD_BLOCK_INFO_PROG) \
	$(DUMP_BLOCK_LIST_PROG)
PROGRAM_FILES = $(SIMULINK_DRIVER_PROGFILE) $(RTW_TEST_PROGFILE) \
	$(XML_TEST_PROGFILE) $(BLXML2CODE_PROGFILE) \
	$(LLVM_PASS_SHLIB) \
	$(ADD_BLOCK_INFO_PROGFILE) $(DUMP_BLOCK_LIST_PROGFILE)
endif

CODE_FILES = $(SIMULINK_DRIVER_SRC) $(RTW_TEST_SRC) $(XML_TEST_SRC) \
	$(RTW_SRCS) $(RTW_HDRS) $(XML_SRCS) $(XML_HDRS) \
	$(BLXML2CODE_SRC) $(LLVM_PASS_SRCS) $(LLVM_PASS_HDRS) \
	$(SHIM_LLVM_SRCS) $(SHIM_LLVM_HDRS) \
	$(BLXML_LLVM_SRCS) $(BLXML_LLVM_HDRS) \
	$(BOOST_LLVM_SRCS) $(BOOST_LLVM_HDRS) \
	$(ADD_BLOCK_INFO_SRC) $(DUMP_BLOCK_LIST_SRC)

DIST_FILES = $(MAKEFILE_LIST)
DIST_FILES += README.txt
DIST_FILES += SimulinkXSD.xlsx
DIST_FILES += $(SIMULINK_XML_SCHEMA_M4) $(SIMULINK_DOXYGEN)
DIST_FILES += $(CODE_FILES)

DIST_LIST = $(patsubst %,$(lastword $(subst /, ,$(shell pwd)))/%,$(DIST_FILES))

DISTCLEAN_FILES = $(XSD_FILES) $(SHIM_XSD_SRCS) $(SHIM_XSD_HDRS)

.PHONY : program library clean distclean depend \
	test_rtw test_sim test doxygen gdbinit prepare_test ctags etags


ifeq ($(DISTRIB),y)
DISTCLEAN_FILES += $(SIMULINK_XML_NS_HDR)
else
DISTCLEAN_FILES += $(SIMULINK_XML_SCHEMA) $(SIMULINK_XML_NS_HDR)
endif

ifdef SHIM_XSD_VERSION
CPPFLAGS += -DSHIM_XSD_VERSION=$(SHIM_XSD_VERSION)
endif

all: program

library: $(ARCHIVE_MEMBER)

program: library $(PROGRAM)

ifneq ($(DISTRIB),y)
#$(SIMULINK_XML_SCHEMA): $(MAKEFILE_LIST)
$(SIMULINK_XML_SCHEMA): $(SIMULINK_XML_SCHEMA_M4)
ifeq ($(GNU_M4),y)
	$(M4) -P -D__NAMESPACE__="$(strip $(SIMULINK_URL))" $< > $@
else
	@echo $(M4) is not GNU m4, please using GNU m4
	@exit 1
endif
endif

$(SIMULINK_XML_NS_HDR): # $(MAKEFILE_LIST)
	def=`echo $@ | tr '[a-z]' '[A-Z]' | sed 's/\./_/g'`; \
	( \
	echo "#ifndef $$def"; \
	echo ""; \
	echo "#ifndef SIMULINKMODEL_NS"; \
	echo "#define SIMULINKMODEL_NS \"$(strip $(SIMULINK_URL))\""; \
	echo "#endif /* $SIMULINKMODEL_NS */"; \
	echo ""; \
	echo "#endif /* $$def */"; \
	) > $@

$(SIMULINK_DRIVER_PROG): $(SIMULINK_DRIVER_OBJ)
$(SIMULINK_DRIVER_PROG): $(LIBRARY)
$(SIMULINK_DRIVER_OBJ): $(SIMULINK_DRIVER_SRC) $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(SIMULINK_XSD_OBJ): $(SIMULINK_XSD_SRC) $(SIMULINK_XSD_HDR)
$(SIMULINK_XSD_OBJ): CXXFLAGS += $(PIC_OPTION) $(XSD_OPT)
$(SIMULINK_DOXYGEN):
	doxygen -g $(SIMULINK_DOXYGEN)

$(RTW_OBJS): $(RTW_SRCS) $(RTW_HDRS) $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(RTW_TEST_OBJ): $(RTW_HDRS) $(SIMULINK_XSD_HDR)  $(SIMULINK_XML_NS_HDR)

$(RTW_TEST_PROG): $(RTW_TEST_OBJ) $(RTW_OBJS)
$(RTW_TEST_PROG): $(LIBRARY)
$(RTW_TEST_PROG): LDLIBS += $(BOOST_LIB)

$(XML_TEST_PROG) : $(XML_TEST_OBJ)
$(XML_TEST_PROG) : $(LIBRARY)
$(XML_TEST_PROG) : LDLIBS += $(GRAPHVIZ_LIB) $(BOOST_LIB)
$(XML_TEST_OBJ): CPPFLAGS += -I$(GRAPHVIZ_ROOT)/include/graphviz
$(XML_TEST_OBJ): $(XML_HDRS) $(SIMULINK_XML_NS_HDR)
$(XML_OBJS): $(XML_HDRS)

$(BLXML2CODE_PROG) : $(BLXML2CODE_OBJ)
$(BLXML2CODE_PROG) : $(LIBRARY)
$(BLXML2CODE_OBJ): $(SIMULINK_XML_NS_HDR)

$(ADD_BLOCK_INFO_PROG) : $(ADD_BLOCK_INFO_OBJ)
$(ADD_BLOCK_INFO_PROG) : $(LIBRARY)
$(ADD_BLOCK_INFO_OBJ) : $(SIMULINK_XML_NS_HDR)

$(DUMP_BLOCK_LIST_PROG) : $(DUMP_BLOCK_LIST_OBJ)
$(DUMP_BLOCK_LIST_PROG) : $(LIBRARY)
$(DUMP_BLOCK_LIST_OBJ) : $(SIMULINK_XML_NS_HDR)

$(SHIM_XSD_OBJS) : CXXFLAGS += $(XSD_OPT)

ifeq ($(LLVM_PASS_DEBUG),y)
$(LLVM_PASS_OBJS) : CXXFLAGS += $(LLVM_NOOPT_CXXFLAGS)
else
$(LLVM_PASS_OBJS) : CXXFLAGS += $(LLVM_CXXFLAGS)
endif
$(LLVM_PASS_DEPS) : CXXFLAGS += $(LLVM_CXXFLAGS)
ifneq ($(IS_MINGW),n)
$(LLVM_PASS_SHLIB) : LDFLAGS += -L$(XERCES_LIBDIR)
$(LLVM_PASS_SHLIB) : LDLIBS += $(XERCES_LIBS) $(LLVM_LIBS) -lboost_graph$(BOOSTLIB_EXT) $(LLVM_SYSTEM_LIBS)
else
$(LLVM_PASS_SHLIB) : LDFLAGS += -L/usr/local/lib
$(LLVM_PASS_SHLIB) : LDLIBS += $(LLVM_LDFLAGS) $(LLVM_LIBS) -lboost_graph
endif
$(LLVM_PASS_SHLIB) : $(LLVM_PASS_OBJS) $(LLVM_PASS_SUB_OBJS) $(SIMULINK_XSD_OBJ)
$(LLVM_PASS_SUB_OBJS): CXXFLAGS += $(PIC_OPTION)
$(BOOST_LLVM_OBJS) : CXXFLAGS += $(LLVM_OTHER_CXXFLAGS)

$(LIBRARY): library

clean:
	rm -f *.o $(LIBRARY)
	rm -f $(PROGRAM_FILES) *.log *.dot *.png

distclean: clean
	rm -f *.d $(DISTCLEAN_FILES)

gdbinit:
	echo set args \
	$(TEST_RTW_FILE_OPTIONS) \
	$(TEST_RTW_TARGET_XML) $(TEST_RTW_TARGET_OUT) \
	"> $(TEST_RTW_TARGET_LOG) 2>&1" > .gdbinit

prepare_test:
	xml_schema=`dirname $(TEST_RTW_TARGET_XML)`/$(SIMULINK_XML_SCHEMA);\
	if test -L $$xml_schema -o -f $$xml_schema; \
	then \
		if cmp -s $(SIMULINK_XML_SCHEMA) $$xml_schema; \
		then :;\
		else \
			rm -f $$xml_schema;\
			ln -s `pwd`/$(SIMULINK_XML_SCHEMA) $$xml_schema;\
		fi;\
	else \
		ln -s `pwd`/$(SIMULINK_XML_SCHEMA) $$xml_schema;\
	fi

test_rtw: $(RTW_TEST_PROG) prepare_test
ifeq ($(TEST_RTW_TARGET_XML),none)
	@echo TEST_TARGET error 1>&2
	@exit 1
else
	./$(RTW_TEST_PROG) \
	$(TEST_RTW_FILE_OPTIONS) \
	$(TEST_RTW_TARGET_XML) $(TEST_RTW_TARGET_OUT) \
	> $(TEST_RTW_TARGET_LOG) 2>&1
endif

test_sim: $(SIMULINK_DRIVER_PROG) test_rtw prepare_test
ifeq ($(TEST_RTW_TARGET_OUT),none)
	@echo TEST_TARGET error 1>&2
	@exit 1
else
	./$(SIMULINK_DRIVER_PROG) $(TEST_RTW_TARGET_OUT) $(TEST_SIMULINK_TARGET_OUT) \
	> $(TEST_SIMULINK_TARGET_LOG) 2>&1
endif

test_xml: $(XML_TEST_PROG) test_rtw
ifeq ($(TEST_RTW_TARGET_XML),none)
	@echo TEST_TARGET error 1>&2
	@exit 1
else
	./$(XML_TEST_PROG) $(TEST_RTW_TARGET_OUT) $(TEST_DOT_TARGET_OUT) \
	> $(TEST_XML_TARGET_LOG) 2>&1
	$(DOT) -Tpng -o $(TEST_PNG_TARGET_OUT) $(TEST_DOT_TARGET_OUT)
endif

test_blxml: $(BLXML2CODE_PROG) $(LLVM_PASS_SHLIB)
ifeq ($(TEST_RTW_TARGET_OUT),none)
	@echo TEST_TARGET error 1>&2
	@exit 1
else
	./blxml-perf.sh -v -o $(TEST_BLXML_TARGET_OUT) \
		-C $(TEST_BLXML_TARGET_INCLUDE) \
		$(TEST_BLXML_TARGET_OPTIONS) \
		$(TEST_RTW_TARGET_OUT)
endif

ifeq ($(DISTRIB),y)
test: test_rtw test_xml
else
test: test_rtw test_sim test_xml test_blxml
endif

doxygen: $(SIMULINK_DOXYGEN)
	doxygen $(SIMULINK_DOXYGEN)

distlist: $(MAKEFILE_LIST)
	( for i in $(DIST_LIST); do echo $$i; done ) > distlist

etags: TAGS
TAGS : $(CODE_FILES) $(MAKEFILE_LIST)
	etags $(filter %.c %.h %.cxx %.hxx,$^)

ctags: tags
tags: $(CODE_FILES) $(MAKEFILE_LIST)
	ctags $(filter %.c %.h %.cxx %.hxx,$^)

$(SHIM_XSD_SRCS) $(SHIM_XSD_HDRS) : XSD_OPTIONS += $(SHIM_XSD_OPTIONS)
$(SIMULINK_XSD_SRC) $(SIMULINK_XSD_HDR) : XSD_OPTIONS += $(SIMULINK_XSD_OPTIONS)
%.cxx %.hxx: %.xsd
	$(XSD) cxx-tree $(XSD_OPTIONS) $<
%.o: %.cxx
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

# depend
$(RTW_DEPS): $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(XML_DEPS): $(SIMULINK_XSD_HDR)
$(RTW_TEST_DEPS) : $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(XML_TEST_DEPS) : $(SIMULINK_XSD_HDR)
$(SIMULINK_DRIVER_DEPS): $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(BLXML_LLVM_DEPS) : $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(BLXML2CODE_DEPS) : $(SIMULINK_XSD_HDR)
$(BOOST_LLVM_DEPS) : CPPFLAGS += $(LLVM_OTHER_CXXFLAGS)
$(SHIM_LLVM_DEPS) : $(SHIM_XSD_HDRS)
$(ADD_BLOCK_INFO_DEPS) : $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)
$(DUMP_BLOCK_LIST_DEPS) : $(SIMULINK_XSD_HDR) $(SIMULINK_XML_NS_HDR)

%.d: %.cxx
	$(COMPILE.cc) -MM $(OUTPUT_OPTION) $<
%.d: %.c
	$(COMPILE.c) -MM $(OUTPUT_OPTION) $<

%$(DLL_EXT): %.o
	$(LINK.o) -shared $^ $(OUTPUT_OPTION) $(LDLIBS)


depend: $(ALL_DEPS)

-include $(ALL_DEPS)
