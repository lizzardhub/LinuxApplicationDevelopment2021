GENERATES = range
TRASH = *.o *~ o.* *.out *.tmp

all:    $(GENERATES)

%.o:	%.c
		cc $^ -o0 -g -c -o $@

range:	range.o
		cc $^ -o $@

test:	range
		gdb < gdb-test1 2>/dev/null | grep @@@ > gdb-out1.tmp && \
		python -c 'print("\n".join(["@@@ i={} (start=1, end=12, step=1)".format(i) for i in range(1, 12) if i%5==0]))' > test1.tmp && \
		diff gdb-out1.tmp test1.tmp && \
		echo "Test 1 passed" && \
		gdb < gdb-test2 2>/dev/null | grep @@@ > gdb-out2.tmp && \
		python -c 'print("\n".join(["@@@ i={} (start=-100, end=100, step=3)".format(i) for i in range(-100, 100, 3)][27:35]))' > test2.tmp && \
		echo "Test 2 passed"

clean:
		rm -f $(GENERATES) $(TRASH)