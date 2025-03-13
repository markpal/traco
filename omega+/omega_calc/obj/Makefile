# Makefile for release 1.0 of the omega system
# DON'T EDIT -- put any locally required changes in Makefile.config.
# See INSTALL for more details.

TARGET=oc

all: $(TARGET)
$(TARGET): .executable
install: install_executable
depend: depend_executable
clean: clean_self
veryclean: veryclean_self

# Required libraries
REQUIRED=code_gen omega

OBJS = lex.yy.o y.tab.o AST.o
SRCS = lex.yy.c y.tab.c ../src/AST.cc
TARGET_INCL_PATH = -I.
TARGET_CFLAGS = -DOMEGA_BUILD_DATE="\"$(OMEGA_BUILD_DATE)\""

y.tab.c, y.tab.h: ../src/parser.y
	${RUMINANT} -v -d ../src/parser.y

lex.yy.c: ../src/parser.l y.tab.h
	$(LEX) -i ../src/parser.l

BASEDIR=../..
include $(BASEDIR)/Makefile.config
include $(BASEDIR)/Makefile.rules

ifeq ($(shell test -f Makefile.deps && echo "true"), true)
include Makefile.deps
endif