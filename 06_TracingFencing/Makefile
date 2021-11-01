GENERATES = move
TRASH = *.o *~ o.* *.out *.tmp *.log

catte="Hello!"

all:    $(GENERATES)

%.o:	%.c
		cc $^ -o0 -g -c -o $@

move:	move.o
		cc $^ -o $@

test:	move
		head -c 6500000 </dev/urandom >myfile1.tmp
		cp myfile1.tmp myfile1.back.tmp
		@echo "Test file generated"
		tests/test-standard.sh
		tests/test-open1.sh
		tests/test-open2.sh
		tests/test-read.sh
		tests/test-write.sh
		tests/test-close1.sh
		tests/test-close2.sh
		tests/test-remove.sh
		@echo "Tests passed successfully"

clean:
		rm -f $(GENERATES) $(TRASH)