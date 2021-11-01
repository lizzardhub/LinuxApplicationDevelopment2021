GENERATES = move libremove.so
TRASH = *.o *~ o.* *.out *.tmp *.log

all:    $(GENERATES)

%.o:	%.c
		cc $^ -o0 -g -c -o $@

move:	move.o
		cc $^ -o $@

libremove.so: libremove.c
		gcc -shared -fPIC libremove.c -o libremove.so -ldl

prepare-test:	move libremove.so
		head -c 6500000 </dev/urandom >myfile1.tmp
		cp myfile1.tmp myfile1.back.tmp
		@echo "Test file generated"

test:	prepare-test
		tests/test-standard.sh
		tests/test-open1.sh
		tests/test-open2.sh
		tests/test-read.sh
		tests/test-write.sh
		tests/test-close1.sh
		tests/test-close2.sh
		tests/test-remove.sh
		tests/test-remove-ld.sh
		@echo "Tests passed successfully"

clean:
		rm -f $(GENERATES) $(TRASH)