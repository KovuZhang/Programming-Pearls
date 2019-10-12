#include <stdio.h>

#define BITSPERWORD 32	// 假设当前机器int类型占用 32 bit
#define SHIFT 5	// 32 = 2^5		 32是2的5次方
#define MASK 0x1F	// 转换为二进制：11111
#define N 10000000	// 元素个数

int a[1 + N / BITSPERWORD];	// 用int类型数组存储所有元素，每个bit存储表示一个元素

/**
 * 32 = 2^5 => 转换为二进制就是1前面5个0，因为二进制是从2^0开始 => 100000
 * 32/32 = 1 => 32与32相除等于1，从二进制角度看，等于右移5位 => 000001
 * 由上可知，如果一个数的二进制数前5位都是0，那么这个数一定是32的倍数，能被32整除，而且整除的结果为二进制右移5位后的结果
 * 同样，如果一个数不能被32整除，那么这个数的二进制数前5位一定不都是0，而且，二进制数的前5位为这个数与32相除后的余数，二进制数右移5位的结果为这个数与32相除后的商
 * i 表示需要进行操作的第 i 个对象
 * i >> SHIFT 相当于 i/32，可以将 i 定位到具体的数组中
 * i & MASK 相当于 i % 32，可以取 i 的二进制前五位，
 */
void set(int i)
{
	a[i >> SHIFT] |= (1 << (i&MASK));
}

void clr(int i)
{
	a[i >> SHIFT] &= ~(1 << (i&MASK));
}

int test(int i)
{
	return a[i >> SHIFT] & (1 << (i&MASK));
}