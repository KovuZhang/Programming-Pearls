#define BITSPERWORD 32	// 假设当前机器int类型占用 32 bit = 4 Byte
#define SHIFT 5	// 32 = 2^5		 32是2的5次方
#define MASK 0x1F	// 转换为二进制：11111
#define N 10000000	// 元素个数

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

int a[1 + N / BITSPERWORD];	// 用int类型数组存储所有元素，每个bit存储表示一个元素

/**
 * 32 = 2^5 => 转换为二进制就是1前面5个0，因为二进制是从2^0开始 => 100000
 * 32/32 = 1 => 32与32相除等于1，从二进制角度看，等于右移5位 => 000001
 *
 * 由上可知，如果一个数的二进制数前5位都是0，那么这个数一定是32的倍数，能被32整除，而且整除的结果为二进制右移5位后的结果
 * 同样，如果一个数不能被32整除，那么这个数的二进制数前5位一定不都是0，而且，二进制数的前5位为这个数与32相除后的余数，二进制数右移5位的结果为这个数与32相除后的商
 *
 * 对乘法而言，1*32 = 32 => 1与32相乘等于32，从二进制角度看，等于左移5位，即在左边加5个0 => 000001 -> 100000
 *
 * 总结：对于位运算，一个二进制数左移等于乘以2的倍数，右移等于除以2的倍数。左移n位等于乘以2的n次方，右移n位等于除以2的n次方。其中，对于右移操作，二进制数右移前的前n位为除后的余数，右移后的结果为除后的商。
 */


/**
 * i 表示需要进行操作的第 i 个对象
 * i >> SHIFT 相当于 i/32，将 i 定位到具体的数组中
 * i & MASK 相当于 i % 32，取 i 的二进制前五位，即除以32后的余数，在本次32位int类型的对象中处于第几位，将1左移余数位指从32位二进制位的顺序上将对应位置的比特位设为1（余数不可能为32，因此余数是0~31）
 */


/**
 * a[i >> SHIFT] 的值的二进制数初始情况下为0，（1 << (i&MASK)）将对应位的二进制值设置位1，与 a[i >> SHIFT] 进行 '|' 或操作后，（1 << (i&MASK)）将对应位的二进制值得以保留。
 */
// 设置比特位
void setBit(int i)
{
	a[i >> SHIFT] |= (1 << (i&MASK));
}

/**
 * （1 << (i&MASK)）将对应位的二进制值设置位1，取反后对应位为0，其他位为1。与 a[i >> SHIFT] 进行 '&' 与操作后，将清除（1 << (i&MASK)）对应位，即将二进制值修改为0。
 */
// 清除比特位
void clearBit(int i)
{
	a[i >> SHIFT] &= ~(1 << (i&MASK));
}

/**
 * a[i >> SHIFT] 和（1 << (i&MASK)）做'&'与操作，因为（1 << (i&MASK)）除了第（i&MASK）+ 1 位为 1，其他位都是 0.因此与操作之后 a[i >> SHIFT] 只会保留第（i&MASK）+ 1 位的值，其他位都会是 0.
 * 因此只需判断返回值是否是 0 就可以知道第（i&MASK）+ 1 位是否为 1.
 */
// 判断该元素是否存入数组
int testBit(int i)
{
	return a[i >> SHIFT] & (1 << (i&MASK));
}

// 随机选择 x 与 y 之间的整数
int randomint(int x, int y)
{
	srand((unsigned)time(NULL));
	return (RAND_MAX*rand() + rand()) % (y - x + 1) + x;
}

// 生成文件
void setValue(int * x, int len)
{
	for (int i = 0; i < len; i++)
	{
		x[i] = i;
	}

	for (int i = 0; i < len; i++)
	{
		int original = i;
		int randNum = randomint(i, len - 1);
		std::swap(x[original], x[randNum]);
	}
}

int main(void)
{
	int numbers[10000000];

	clock_t startCreateNumbers = clock();
	setValue(numbers, 10000000);
	clock_t finishCreateNumbers = clock();

	double duration = (double)(finishCreateNumbers - startCreateNumbers) / CLOCKS_PER_SEC;
	printf("Load Numbers: %f seconds\n", duration);

	clock_t start = clock();

	// 初始化
	for (int i = 0; i < N; i++)
	{
		clearBit(i);
	}

	// 保存整数
	for (int i = 0; i < N / 10; i++)
	{
		setBit(numbers[i]);
	}

	clock_t finish = clock();

	// 时间开销
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("Sort Number: %f seconds\n", duration);

	getchar();
	return 0;
}