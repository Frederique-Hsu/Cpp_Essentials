# File name     : Makefile
# Description   : This script tells how to build current project.
# Author        : Frederique Hsu
# Date          : Sun.  20 Aug. 2023
# 


PROJECT = Functions

CXX = g++
CXXFLAGS = -g -Wall -std=c++11
INCLUDES = 
LIBS = -lpthread -lgtest

SRC_EXTENSIONS = .c .cpp .cxx .cc .c++
HDR_EXTENSIONS = .h .hpp .hxx .hh .h++

CURRENT_DIR = .
DIRS = $(shell find $(CURRENT_DIR) -maxdepth 5 -type d)
SOURCES = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(SRC_EXTENSIONS))))
HEADERS = $(foreach dir, $(DIRS), $(wildcard $(addprefix $(dir)/*, $(HDR_EXTENSIONS))))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))


.PHONY : all rebuild clean show

all : $(PROJECT)

$(PROJECT) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDES) $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.c++
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	-rm -frv $(OBJECTS)
	-rm -frv $(PROJECT)
	-rm -frv *.out

rebuild : clean all

show :
	@echo "DIRS = " $(DIRS)
	@echo "SOURCES = " $(SOURCES)
	@echo "HEADERS = " $(HEADERS)
	@echo "OBJECTS = " $(OBJECTS)
