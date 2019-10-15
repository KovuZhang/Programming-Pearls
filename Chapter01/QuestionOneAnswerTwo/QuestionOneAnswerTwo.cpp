#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define N 10000000

int intcomp(const void *x, const void *y)
{
	return *(int*)x - *(int*)y;
}

int a[N / 10];

int randint(int x, int y)
{
	srand((unsigned)time(NULL));
	return (RAND_MAX*rand() + rand()) % (y - x + 1) + x;
}

void setValue(int * result)
{
	int temp[N];

	for (int i = 0; i < N; i++)
	{
		temp[i] = i;
	}

	for (int i = 0; i < N; i++)
	{
		int original = i;
		int randNum = randint(i, N - 1);
		std::swap(temp[original], temp[randNum]);
	}

	for (int i = 0; i < N / 10; i++)
	{
		result[i] = temp[i];
	}
}

int main(void)
{
	setValue(a);
	
	clock_t start = clock();
	qsort(a, N / 10, sizeof(int), intcomp);
	clock_t finish = clock();

	double duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("Sort Number: %f seconds\n", duration);

	getchar();
	return 0;
}