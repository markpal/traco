all: libomega.a libcode_gen.a oc

BASEDIR =.

oc: always
	cd omega_calc/obj; $(MAKE) oc

libomega.a: always
	cd omega_lib/obj; $(MAKE) libomega.a

libcode_gen.a: always
	cd code_gen/obj; $(MAKE) libcode_gen.a

install: install_all
depend: depend_all
clean: clean_all
veryclean: veryclean_all

SUBMAKE=$(MAKE)

include $(BASEDIR)/Makefile.config
include $(BASEDIR)/Makefile.rules
