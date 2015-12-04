#
# Makefile for some system calls covered in 1730. 
# @author Michael E. Cotterell <mepcott@uga.edu>
#
# If you decide to modify the examples in place, then please consider the
# following... This Makefile makes the following assumptions about each example:
# 
#  1. Is self-contained inside of its source (.cpp) file.
#  2. Source file contains a main function.
#  3. Source file does not include any non-standard headers.
#  4. If the source file is called %.cpp, then the target executable is %.
#

CC = g++
DEBUG = -g -Wall -O0 -pedantic-errors
CFLAGS=-std=c++11
LFLAGS=-std=c++11
COMPILE=$(CC) $(DEBUG) $(CFLAGS) -c
LINK=$(CC) $(DEBUG) $(LFLAGS)
RM=rm -f

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
EXE=$(OBJ:%.o=%)

.SUFFIXES: .cpp .o
.PHONY: clean all

all: $(EXE)

$(filter %.o, $(OBJ)): %.o: %.cpp
	$(COMPILE) $<

$(filter %, $(EXE)): %: %.o
	$(LINK) -o $@ $<

clean:
	@$(foreach exe, $(EXE), echo $(RM) $(exe); ($(RM) $(exe)) || exit;)
	@$(foreach obj, $(OBJ), echo $(RM) $(obj); ($(RM) $(obj)) || exit;)

