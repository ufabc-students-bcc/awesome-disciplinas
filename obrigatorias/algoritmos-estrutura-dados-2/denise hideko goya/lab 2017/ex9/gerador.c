#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) 
{
	long int i, n;

	srand(1999);

	n = 10000000;
	
	long int *buf = (long int*) malloc(sizeof(long int) * n);
	
	for(i = 0; i < n; i++)
		buf[i] = i;
	
	for(i = 0; i < n; i++)
	{
		long int j = rand() % n;
		if(j != i)
		{
			long int aux = buf[i];
			buf[i] = buf[j];
			buf[j] = aux;
		}
	}
	
	printf("%ld\n", n);
	
	for (i=0; i<n; i++)
		printf("%07ld\n", buf[i]);

	free(buf);
	
	return 0;
}
