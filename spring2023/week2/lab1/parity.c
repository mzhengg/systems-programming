#include <stdio.h>

int main(void)
{
  unsigned int v = 19;
  char parity = 0;
  while(v){
    parity = !parity;
    v = v & (v - 1);
  }
  return 0;
}