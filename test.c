#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

int main()
{
	int *a;
	int i = 0;

	a = 0;
	srand(time(NULL));
	printf("%d\n", rand() % 10 + 1);
}

