# File name		: Makefile
# Description	: This script tells how to build current project.
# 


PROJECT = Functions

CXX = clang++-18
CXXFLAGS = -g -Wall -std=c++23
INCLUDES = 
LIBS = -lgtest -lpthread


SRC_EXTENSIONS = .c .cpp .c++ .cxx .cc
HDR_EXTENSIONS = .h .hpp .h++ .hxx .hh

CURR_DIR = .
DIRS = ${shell find ${CURR_DIR} -maxdepth 5 -type d}
SOURCES = ${foreach dir, ${DIRS}, ${wildcard ${addprefix ${dir}/*, ${SRC_EXTENSIONS}}}}
HEADERS = ${foreach dir, ${DIRS}, ${wildcard ${addprefix ${dir}/*, ${HDR_EXTENSIONS}}}}
OBJECTS = ${addsuffix .o, ${basename ${SOURCES}}}

.PHONY : all clean rebuild show

all : ${PROJECT}

${PROJECT} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@ ${INCLUDES} ${LIBS}

%.o : %.c
	${CXX} ${CXXFLAGS} -c $< -o $@

%.o : %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

%.o : %.c++
	${CXX} ${CXXFLAGS} -c $< -o $@

%.o : %.cxx
	${CXX} ${CXXFLAGS} -c $< -o $@

%.o : %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

clean :
	-rm -frv ${PROJECT}
	-rm -frv ${OBJECTS}
	-rm -frv *.out

rebuild : clean all

show :
	@echo "PROJECT = " ${PROJECT}
	@echo "SOURCES = " ${SOURCES}
	@echo "HEADERS = " ${HEADERS}
	@echo "OBJECTS = " ${OBJECTS}
	@echo "DIRS = " ${DIRS}