#include<stdio.h>
#include<string.h>

void StrInsert(char *str1,char *str2,int n);
int main()
{
	char str1[20] = "abcdef";
	char *str2 = "12345";

	StrInsert(str1,str2,2);
	printf("%s\n",str1);

	return 0;
}

void StrInsert(char *str1,char *str2,int n)
{
	//1.�ҵ������λ��
	char *pInsert = str1 + n - 1;
	//2.�ҵ��ƶ���λ��
	char *pMove = str1 + strlen(str1);
	//3.�Ӻ���ǰ�ƶ����ƶ���str2���ȵ�λ��
	while (pInsert <= pMove)
	{
		*(pMove+strlen(str2)) = *pMove;
		pMove--;
	}
	//4.����str2���Ӳ���λ�ÿ�ʼ����
	while (*str2 != '\0')
	{
		*pInsert = *str2;
		pInsert++;
		str2++;
	}
}