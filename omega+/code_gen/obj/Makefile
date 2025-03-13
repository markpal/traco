# Makefile for release 1.0 of the omega system
# DON'T EDIT -- put any locally required changes in Makefile.config.
# See INSTALL for more details.

LIB=code_gen
LIB_NAME=lib$(LIB).a
TARGET=$(LIB_NAME)

all: $(TARGET)
$(TARGET): .library
install: install_library install_includes
depend: depend_library
clean: clean_self
veryclean: veryclean_self

# Required libraries
REQUIRED=omega

TARGET_LIBS =
TARGET_LIB_PATH =
TARGET_INCL_PATH =

BASIC_SRC = ../src/CG_stringBuilder.cc ../src/spmd.cc ../src/CG_stringRepr.cc ../src/code_gen.cc ../src/stmt_builder.cc ../src/elim.cc
BASIC_OBJ = $(BASIC_SRC:../src/%.cc=%.o)

SUIF_SRC = ../src/CG_suifRepr.cc ../src/CG_suifBuilder.cc
SUIF_OBJ = $(SUIF_SRC:../src/%.cc=%.o)

MMAP_SRC = ../src/mmap-codegen.cc ../src/mmap-util.cc ../src/mmap-checks.cc ../src/mmap-sub.cc
MMAP_OBJ = $(MMAP_SRC:../src/%.cc=%.o)

OBJS = ${BASIC_OBJ} ${MMAP_OBJ}
SRCS = ${BASIC_SRC} ${MMAP_SRC}

BASEDIR=../..
include $(BASEDIR)/Makefile.config

ifeq ($(BUILD_SUIF), true)
OBJS := $(OBJS) $(SUIF_OBJ)
SRCS := $(SRCS) $(SUIF_SRC)
TARGET_LIBS := $(TARGET_LIBS) -lsuif1
TARGET_LIB_PATH := $(TARGET_LIB_PATH) -L${SUIFHOME}/i386-linux/solib
TARGET_INCL_PATH := $(TARGET_INCL_PATH) -I${SUIFHOME}/include
endif

include $(BASEDIR)/Makefile.rules

# suppress warning of constant char * conversion nuiance in suif
$(SUIF_OBJ): %.o: ../src/%.cc
	$(CC) -Wno-write-strings $(CFLAGS) -c $< -o $@

ifeq ($(shell test -f Makefile.deps && echo "true"), true)
include Makefile.deps
endif