#include <stdio.h>
#include <algorithm>

int intcomp(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int a[1000000];

int main(void)
{
	int n = 0;
	
	printf("Hello World\n");

	for (int i = 9999999; i > 9000000; i--)
	{
		a[n] = i;
		n++;
		if (i % 10000 == 0)
		{
			printf("%d %d\n", a[n-1], n-1);
		}
	}
	
	qsort(a, n, sizeof(int), intcomp);

	for (int i = 0; i < n; i++)
	{
		printf("%d\n", a[i]);
	}

	return 0;
}