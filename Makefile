PREFIX?=/usr/local
CFLAGS?=-O2 -pipe
CFLAGS+=-I $(PREFIX)/include -I $(CURDIR)/src/lib -I $(CURDIR)/src/ext
CFLAGS+=-std=c99 -Wall -Werror -Wpedantic -Wextra -fPIC \
        -Wpointer-arith \
        -Wcast-align \
        -Wno-unused-parameter \
        -Wdeclaration-after-statement \
        -Wcast-qual \
        -Wstrict-prototypes \
        -Wmissing-prototypes \
        -Wno-sign-compare \
        -Wshadow
LDFLAGS+=-L $(PREFIX)/lib

CMD_SRC:=$(wildcard src/cmd/*.c)
CMD_DEP:=$(CMD_SRC:%.c=obj/%.d)
CMD_OBJ:=$(CMD_SRC:%.c=obj/%.o)
CMD_AIM:=$(CMD_SRC:src/cmd/%.c=bin/%)

LIB_SRC:=$(wildcard src/lib/*.c)
LIB_DEP:=$(LIB_SRC:%.c=obj/%.d)
LIB_OBJ:=$(LIB_SRC:%.c=obj/%.o)

ifeq ($(32bit),yes)
  CFLAGS+=-m32
  LDFLAGS+=-m32
endif

ifeq ($(assert),no)
  CFLAGS+=-DNDEBUG
endif

ifeq ($(debug),yes)
  CFLAGS+=-g
endif

all: lib/libpocsec.a $(CMD_OBJ) $(CMD_AIM)

lib/libpocsec.a: $(LIB_OBJ)
	@echo "[link $(@F)]"
	@test -d $(@D) || mkdir -p $(@D)
	@$(AR) cr $@ $(LIB_OBJ)

# read dependencies
-include $(CMD_DEP) \
         $(LIB_DEP)

bin/%: obj/src/cmd/%.o
	@echo "[link $(@F)]"
	@test -d $(@D) || mkdir -p $(@D)
	@$(CC) $^ $(LDFLAGS) -o $@

obj/%.o: %.c
	@echo "[compile $(@F)]"
	@test -d $(@D) || mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@$(CC) -c $< -o $(@:.o=.d) $(CFLAGS) -MM -MP -MT $@

.PHONY: cfmt clean cleanup test
cfmt:
	clang-format -i src/cmd/*.[ch] src/lib/*.[ch]

clean:
	rm -rf obj

cleanup: clean
	rm -rf bin lib

test: all
	valgrind --tool=memcheck --leak-check=full ./bin/pocsec_test
