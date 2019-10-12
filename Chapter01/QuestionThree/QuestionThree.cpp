#include <stdio.h>

#define BITSPERWORD 32	// ���赱ǰ����int����ռ�� 32 bit
#define SHIFT 5	// 32 = 2^5		 32��2��5�η�
#define MASK 0x1F	// ת��Ϊ�����ƣ�11111
#define N 10000000	// Ԫ�ظ���

int a[1 + N / BITSPERWORD];	// ��int��������洢����Ԫ�أ�ÿ��bit�洢��ʾһ��Ԫ��

/**
 * 32 = 2^5 => ת��Ϊ�����ƾ���1ǰ��5��0����Ϊ�������Ǵ�2^0��ʼ => 100000
 * 32/32 = 1 => 32��32�������1���Ӷ����ƽǶȿ�����������5λ => 000001
 * ���Ͽ�֪�����һ�����Ķ�������ǰ5λ����0����ô�����һ����32�ı������ܱ�32���������������Ľ��Ϊ����������5λ��Ľ��
 * ͬ�������һ�������ܱ�32��������ô������Ķ�������ǰ5λһ��������0�����ң�����������ǰ5λΪ�������32������������������������5λ�Ľ��Ϊ�������32��������
 * i ��ʾ��Ҫ���в����ĵ� i ������
 * i >> SHIFT �൱�� i/32�����Խ� i ��λ�������������
 * i & MASK �൱�� i % 32������ȡ i �Ķ�����ǰ��λ��
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