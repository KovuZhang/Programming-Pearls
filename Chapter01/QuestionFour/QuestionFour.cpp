#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <random>

constexpr auto N = 20;

int randint(int x, int y)
{
	srand((unsigned)time(NULL));
	return rand() % (y - x + 1) + x;
}

int main(void)
{
	int x[20];
	
	for (int i = 0; i < N; i++)
	{
		x[i] = i;
	}

	for (int i = 0; i < 15; i++)
	{
		int a = i;
		int b = randint(i, N - 1);
		std::swap(x[a], x[b]);
	}

	getchar();
	return 0;
}