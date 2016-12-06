MAKE_DIR := $(PWD)

LIB_DIR := ${MAKE_DIR}/libs
LIB_SRCH_PATH := -L${LIB_DIR}

LIBS := -pthread 

INCLUDE_PATH :=
INCLUDE_PATH += -I${LIB_DIR}
INCLUDE_PATH += -I${LIB_DIR}/asio-1.10.6/include
INCLUDE_PATH += -I${LIB_DIR}/asio-1.10.6/include/asio
INCLUDE_PATH += -I${LIB_DIR}/rapidjson

CC := g++
CCFLAGS :=
CCFLAGS += -Wall -Wfatal-errors -Wextra 
CCFLAGS += ${INCLUDE_PATH} ${LIB_SRCH_PATH}

LDFLAGS :=
LDFLAGS += ${LIBS} ${CCFLAGS} -g


## Trying to be cross-platform
OS := $(shell uname)

ifeq (${OS}, Windows)
	OSFILTER += Linuxconsole.cpp
endif
ifeq (${OS}, Linux)
	OSFILTER += Winconsole.cpp
endif

SRCS := $(filter-out $(OSFILTER), $(wildcard *.cpp))
OBJS := $(SRCS:.cpp=.o)
HEADERS := $(wildcard *.h)
PROG := SpideR

###########################################

all : ${PROG}

${PROG} : ${SRCS}
	${CC} -o $@ $^ ${LDFLAGS} 


.PHONY : print
print:
	@echo -e "Sources: ${SRCS} \nObjects: ${OBJS} \nHeaders: ${HEADERS}\n"

.PHONY : clean
clean:
	rm -rf ${OBJS} ${PROG}








