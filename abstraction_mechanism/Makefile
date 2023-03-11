# File		Makefile
# Brief		This script tells how to build current project.
# 

PROJECT = abstraction_mechanism

CXX = g++
CXXFLAGS = -g -Wall -std=c++20
OPTS = -Wno-deprecated -DDEBUG
INCLUDES = 
LIBS = -lgtest -lgmock -lpthread


SRC_EXTENSIONS = .c .cpp .c++ .cc .cxx
HDR_EXTENSIONS = .h .hpp .h++ .hh .hxx

CUR_DIR = .
DIRS = ${shell find ${CUR_DIR} -maxdepth 5 -type d}
SOURCES = ${foreach dir, ${DIRS}, ${wildcard ${addprefix ${dir}/*, ${SRC_EXTENSIONS}}}}
HEADERS = ${foreach dir, ${DIRS}, ${wildcard ${addprefix ${dir}/*, ${HDR_EXTENSIONS}}}}
OBJECTS = ${addsuffix .o, ${basename ${SOURCES}}}

BASENAMES = ${basename ${SOURCES}}

.PHONY : all clean rebuild show

all : ${PROJECT}

${PROJECT} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@ ${INCLUDES} ${LIBS}
	-mkdir build
	-mv $^ build/

%.o : %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ $(OPTS)

%.o : %.c++
	${CXX} ${CXXFLAGS} -c $< -o $@ $(OPTS)

%.o : %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ $(OPTS)

%.o : %.cxx
	${CXX} ${CXXFLAGS} -c $< -o $@ $(OPTS)

%.o : %.c
	${CXX} ${CXXFLAGS} -c $< -o $@ $(OPTS)

clean :
	-rm -frv ${OBJECTS}
	-rm -frv ${PROJECT}
	-rm -frv *.out

rebuild : clean all

show :
	@echo "PROJECT = " ${PROJECT}
	@echo "SOURCES = " ${SOURCES}
	@echo "HEADERS = " ${HEADERS}
	@echo "OBJECTS = " ${OBJECTS}
	@echo "DIRS = " ${DIRS}
	@echo "BASENAMES = " ${BASENAMES}
