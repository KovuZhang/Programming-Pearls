// QuestionOne.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <set>

#define N 10000000

int randint(int x, int y)
{
	srand((unsigned)time(NULL));
	return (RAND_MAX*rand() + rand()) % (y - x + 1) + x;
}

void setValue(int * x)
{
	for (int i = 0; i < N; i++)
	{
		x[i] = i;
	}

	for (int i = 0; i < N; i++)
	{
		int original = i;
		int randNum = randint(i, N - 1);
		std::swap(x[original], x[randNum]);
	}
}

int main()
{
	std::set<int> s;
	std::set<int>::iterator j;
	
	int numbers[N];
	setValue(numbers);

	clock_t start = clock();
	for (int i = 0; i < N / 10; i++)
	{
		s.insert(numbers[i]);
	}

	clock_t finish = clock();

	std::cout << "Sort Number: " << (double)(finish - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
