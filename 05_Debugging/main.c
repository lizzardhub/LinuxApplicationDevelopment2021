#include <stdio.h>

int tst(long *p) {
  long x;
  x = (long) p;
  return 0;
}

int tst2() {
  long int *a;
  *a = 42;
  return 0;
}

int main(int argc, char *argv[]) {
        long b=7;
        tst(&b);
        tst2();
        printf("⇒ %ld\n", b);
        return 0;
}