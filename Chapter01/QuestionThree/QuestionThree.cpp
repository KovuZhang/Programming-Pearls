#define BITSPERWORD 32	// ���赱ǰ����int����ռ�� 32 bit = 4 Byte
#define SHIFT 5	// 32 = 2^5		 32��2��5�η�
#define MASK 0x1F	// ת��Ϊ�����ƣ�11111
#define N 10000000	// Ԫ�ظ���

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

int a[1 + N / BITSPERWORD];	// ��int��������洢����Ԫ�أ�ÿ��bit�洢��ʾһ��Ԫ��

/**
 * 32 = 2^5 => ת��Ϊ�����ƾ���1ǰ��5��0����Ϊ�������Ǵ�2^0��ʼ => 100000
 * 32/32 = 1 => 32��32�������1���Ӷ����ƽǶȿ�����������5λ => 000001
 *
 * ���Ͽ�֪�����һ�����Ķ�������ǰ5λ����0����ô�����һ����32�ı������ܱ�32���������������Ľ��Ϊ����������5λ��Ľ��
 * ͬ�������һ�������ܱ�32��������ô������Ķ�������ǰ5λһ��������0�����ң�����������ǰ5λΪ�������32������������������������5λ�Ľ��Ϊ�������32��������
 *
 * �Գ˷����ԣ�1*32 = 32 => 1��32��˵���32���Ӷ����ƽǶȿ�����������5λ��������߼�5��0 => 000001 -> 100000
 *
 * �ܽ᣺����λ���㣬һ�������������Ƶ��ڳ���2�ı��������Ƶ��ڳ���2�ı���������nλ���ڳ���2��n�η�������nλ���ڳ���2��n�η������У��������Ʋ�����������������ǰ��ǰnλΪ��������������ƺ�Ľ��Ϊ������̡�
 */


/**
 * i ��ʾ��Ҫ���в����ĵ� i ������
 * i >> SHIFT �൱�� i/32���� i ��λ�������������
 * i & MASK �൱�� i % 32��ȡ i �Ķ�����ǰ��λ��������32����������ڱ���32λint���͵Ķ����д��ڵڼ�λ����1��������λָ��32λ������λ��˳���Ͻ���Ӧλ�õı���λ��Ϊ1������������Ϊ32�����������0~31��
 */


/**
 * a[i >> SHIFT] ��ֵ�Ķ���������ʼ�����Ϊ0����1 << (i&MASK)������Ӧλ�Ķ�����ֵ����λ1���� a[i >> SHIFT] ���� '|' ������󣬣�1 << (i&MASK)������Ӧλ�Ķ�����ֵ���Ա�����
 */
// ���ñ���λ
void setBit(int i)
{
	a[i >> SHIFT] |= (1 << (i&MASK));
}

/**
 * ��1 << (i&MASK)������Ӧλ�Ķ�����ֵ����λ1��ȡ�����ӦλΪ0������λΪ1���� a[i >> SHIFT] ���� '&' ������󣬽������1 << (i&MASK)����Ӧλ������������ֵ�޸�Ϊ0��
 */
// �������λ
void clearBit(int i)
{
	a[i >> SHIFT] &= ~(1 << (i&MASK));
}

/**
 * a[i >> SHIFT] �ͣ�1 << (i&MASK)����'&'���������Ϊ��1 << (i&MASK)�����˵ڣ�i&MASK��+ 1 λΪ 1������λ���� 0.��������֮�� a[i >> SHIFT] ֻ�ᱣ���ڣ�i&MASK��+ 1 λ��ֵ������λ������ 0.
 * ���ֻ���жϷ���ֵ�Ƿ��� 0 �Ϳ���֪���ڣ�i&MASK��+ 1 λ�Ƿ�Ϊ 1.
 */
// �жϸ�Ԫ���Ƿ��������
int testBit(int i)
{
	return a[i >> SHIFT] & (1 << (i&MASK));
}

// ���ѡ�� x �� y ֮�������
int randomint(int x, int y)
{
	srand((unsigned)time(NULL));
	return (RAND_MAX*rand() + rand()) % (y - x + 1) + x;
}

// �����ļ�
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

	// ��ʼ��
	for (int i = 0; i < N; i++)
	{
		clearBit(i);
	}

	// ��������
	for (int i = 0; i < N / 10; i++)
	{
		setBit(numbers[i]);
	}

	clock_t finish = clock();

	// ʱ�俪��
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("Sort Number: %f seconds\n", duration);

	getchar();
	return 0;
}