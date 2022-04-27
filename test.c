#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <inttypes.h>

__STATIC_INLINE uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __ASM("msp");
  return(__regMainStackPointer);
}

int main()
{
	system("ls -l");
}

