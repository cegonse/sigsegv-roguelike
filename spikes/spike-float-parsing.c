#include <stdio.h>

int main() {
 union {
    float f;
    unsigned long ul;
    unsigned char b[4];
 } u;
u.b[0] = 0x66;
u.b[1] = 0x66;
u.b[2] = 0x06;
u.b[3] = 0x40;
  printf("%f | %X\n", u.f, u.ul);
  return 0;
}
