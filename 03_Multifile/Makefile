CFLAGS = -fPIC
GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* *.out

all:    $(GENERATES) test distclean

fun.o:	outlib.h

prog:   const.o fun.o prog.o
		cc $^ -o $@

prog-a:	prog.o liboutput_static.a
		cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
		cc -L. $< -loutput -o $@

liboutput_static.a: const.o fun.o
		ar -rcs $@ $^

liboutput.so: const.o fun.o
		cc -shared $^ -o $@

README:	prog
		./$< 2> $@

test:	prog prog-a prog-so
		./prog >o.out 2>&1; \
		./prog-a >a.out 2>&1; \
		LD_LIBRARY_PATH=`pwd` ./prog-so >so.out 2>&1; \
		cmp o.out a.out; \
		cmp o.out so.out; \
		cmp a.out so.out; \
		./prog hello >o.out 2>&1; \
		./prog-a hello >a.out 2>&1; \
		LD_LIBRARY_PATH=`pwd` ./prog-so hello >so.out 2>&1; \
		cmp o.out a.out; \
		cmp o.out so.out; \
		cmp a.out so.out; \
		./prog cmc is best >o.out 2>&1; \
		./prog-a cmc is best >a.out 2>&1; \
		LD_LIBRARY_PATH=`pwd` ./prog-so cmc is best >so.out 2>&1; \
		cmp o.out a.out; \
		cmp o.out so.out; \
		cmp a.out so.out; \

clean:
		rm -f $(TRASH)

distclean:      clean
		rm -rf $(GENERATES)