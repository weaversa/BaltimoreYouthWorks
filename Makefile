EXTRAS = Makefile

HEADERS = include/list_types.h include/youthworks.h			\
include/csv_read.h include/jobs.h include/youths.h include/digraph.h	\
include/matching.h include/workbook.h

SOURCES = src/list_types.c src/csv_read.c src/jobs.c src/youths.c	\
src/digraph.c src/matching.c src/workbook.c

OBJECTS = $(SOURCES:src/%.c=obj/%.o)

YOUTHWORKSLIB = youthworks
CC = gcc
#DBG = -g -O0 -Wall -fstack-protector-all -pedantic
OPT = -march=native -O3 -flto -DNDEBUG -ffast-math -fomit-frame-pointer -finline-functions
INCLUDES = $(INCLUDE) -Iinclude
LIBS = -lcsv -lm -lxlsxwriter -l$(YOUTHWORKSLIB)
LDFLAGS = $(LIB) -Llib
CFLAGS = -std=gnu99 $(DBG) $(OPT) $(INCLUDES)
AR = ar r
RANLIB = ranlib

all: depend lib/lib$(YOUTHWORKSLIB).a

depend: .depend
.depend: $(SOURCES)
	@echo "Building dependencies" 
ifneq ($(wildcard ./.depend),)
	@rm -f "./.depend"
endif
	@$(CC) $(CFLAGS) -MM $^ > .depend
# Make .depend use the 'obj' directory
	@sed -i.bak -e :a -e '/\\$$/N; s/\\\n//; ta' .depend
	@sed -i.bak 's/^/obj\//' .depend
	@rm -f .depend.bak
-include .depend

OBJECTS_HUNGARIAN = lib/weighted-bipartite-perfect-matching/obj/*.o

lib/weighted-bipartite-perfect-matching/lib/libhungarian.a:
	@cd lib/weighted-bipartite-perfect-matching && $(MAKE)

$(OBJECTS): obj/%.o : src/%.c Makefile
	@echo "Compiling "$<""
	@[ -d obj ] || mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

lib/lib$(YOUTHWORKSLIB).a: $(OBJECTS) Makefile lib/weighted-bipartite-perfect-matching/lib/libhungarian.a
	@echo "Creating "$@""
	@[ -d lib ] || mkdir -p lib
	@rm -f $@
	@$(AR) $@ $(OBJECTS_HUNGARIAN)
	@$(AR) $@ $(OBJECTS)
	@$(RANLIB) $@

test/test: test/test.c lib/lib$(YOUTHWORKSLIB).a
	$(CC) $(CFLAGS) $(LDFLAGS) test/test.c -o test/test $(LIBS)

clean: FORCE
	@cd lib/weighted-bipartite-perfect-matching && $(MAKE) clean
	rm -rf *~ */*~ $(OBJECTS) ./.depend test/test *.dSYM test/test.dSYM
	rm -rf lib/lib$(YOUTHWORKSLIB).a

edit: FORCE
	emacs -nw $(SOURCES) $(HEADERS) $(EXTRAS)

FORCE:
