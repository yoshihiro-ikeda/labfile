
USE_PTHREAD=y

CC = gcc
CPPFLAGS += -std=c99 -pedantic

vpath %.c . .. $(TARGET_DIR)
vpath %.h $(TARGET_DIR)

OS := $(shell uname -s)

ifeq ($(OS),MINGW64_NT-6.1)
EXE_EXT = .exe
endif
ifeq ($(OS),MINGW32_NT-6.1)
EXE_EXT = .exe
endif
ifeq ($(OS),CYGWIN_NT-6.1)
EXE_EXT = .exe
endif

CFLAGSe+= -fstack-usage

COPTFLAG = -O2
COPTFLAG += -ffloat-store
CPPFLAGS += -I. -I.. $(patsubst %,-I%,$(TARGET_DIR))
$(shell(echo $(TARGET)))
CFLAGS += $(RTW_SRCS)
CFLAGS += -Wall -Wno-unused-but-set-variable -Wno-unused-variable -g $(COPTFLAG)
CFLAGS += -DCHECK_USER_CYCLE -DMCOS_THREAD_MAX_CYCLE=1

rtGetInf_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rtGetInf.c)
ifeq ($(rtGetInf_exist),rtGetInf.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rtGetInf.c
endif
rtGetNaN_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rtGetNaN.c)
ifeq ($(rtGetNaN_exist),rtGetNaN.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rtGetNaN.c
endif
rt_nonfinite_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rt_nonfinite.c)
ifeq ($(rt_nonfinite_exist),rt_nonfinite.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rt_nonfinite.c
endif
rt_zcfcn_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rt_zcfcn.c)
ifeq ($(rt_zcfcn_exist),rt_zcfcn.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rt_zcfcn.c
endif
rt_look_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rt_look.c)
ifeq ($(rt_look_exist),rt_look.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rt_look.c
endif
rt_look1d_exist := $(shell ls /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210 | grep rt_look1d.c)
ifeq ($(rt_look1d_exist),rt_look1d.c)
CFLAGS += -g /home/yoshi12/matlab/Simulink_XSD_20161024/models/branch_offset_rate210/rt_look1d.c
endif


LDFLAGS += -g
LDLIBS += $(RTW_LIBS) -lm
ifeq ($(USE_PTHREAD),y)
CPPFLAGS += -DUSE_PTHREAD
LDLIBS += -lpthread
endif

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
MAIN_SUS = $(MAIN_SRCS:.c=.su)
PROGRAM = $(MAIN_SRCS:.c=)
PROGRAM_FILE = $(PROGRAM)$(EXE_EXT)
RTW_OBJS = $(RTW_SRCS:.c=.o)
RTW_SUS = $(RTW_SRCS:.c=.su)

RESOURCE_SRC = $(MAIN_SRCS:.c=_res.c)
RESOURCE_OBJ = $(RESOURCE_SRC:.c=.o)
RESOURCE_SUS = $(RESOURCE_SRC:.c=.su)

SUS = $(MAIN_SUS) $(RTW_SUS) $(RESOURCE_SUS)

OBJS = $(MAIN_OBJS) $(RTW_OBJS)

.PHOY: all program clean

all : program

program: $(PROGRAM)

$(PROGRAM): $(MAIN_OBJS)
$(PROGRAM): $(RTW_OBJS)

$(MAIN_OBJS): $(RESOURCE_SRC)
$(RESOURCE_SRC): $(MAIN_SRCS) mcos/genres.pl
	perl mcos/genres.pl $< > $@

clean:
	rm -f $(PROGRAM_FILE) $(RESOURCE_SRC) $(OBJS) $(SUS)
