#
# Makefile for some system calls covered in 1730. 
# @author Michael E. Cotterell <mepcott@uga.edu>
#
# If you decide to modify the examples in place, then please consider the
# following... This Makefile makes the following assumptions about each example:
# 
#  1. Is self-contained inside of its source (.c) file.
#  2. Source file contains a main function.
#  3. Source file does not include any non-standard headers.
#  4. If the source file is called %.c, then the target executable is %.
#

CC = gcc
DEBUG = -g -Wall -O0 -pedantic-errors
CFLAGS=-std=c11
LFLAGS=-std=c11
COMPILE=$(CC) $(DEBUG) $(CFLAGS) -c
LINK=$(CC) $(DEBUG) $(LFLAGS)
RM=rm -f

SRC=$(wildcard *.c)
OBJ=$(SRC:%.cpp=%.o)
EXE=$(OBJ:%.o=%)

.SUFFIXES: .c .o
.PHONY: clean all

all: $(EXE)

$(filter %.o, $(OBJ)): %.o: %.c
	$(COMPILE) $<

$(filter %, $(EXE)): %: %.o
	$(LINK) -o $@ $<

clean:
	@$(foreach exe, $(EXE), echo $(RM) $(exe); ($(RM) $(exe)) || exit;)
	@$(foreach obj, $(OBJ), echo $(RM) $(obj); ($(RM) $(obj)) || exit;)

