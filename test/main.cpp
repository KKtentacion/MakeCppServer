#include <iostream>
#include <bits/types/struct_timeval.h>
using namespace std;
void short_sh_interrupt(int irq,void* dev_id)
{
  int value;
  struct timeval tv;
  value=inb(short_base);
  if(!(value&0x80))return ;
  outb(value&0x7F,short_base);
  do_gettimeofday(&tv);
  
}