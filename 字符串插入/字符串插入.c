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
	//1.找到插入的位置
	char *pInsert = str1 + n - 1;
	//2.找到移动的位置
	char *pMove = str1 + strlen(str1);
	//3.从后向前移动，移动到str2长度的位置
	while (pInsert <= pMove)
	{
		*(pMove+strlen(str2)) = *pMove;
		pMove--;
	}
	//4.遍历str2，从插入位置开始复制
	while (*str2 != '\0')
	{
		*pInsert = *str2;
		pInsert++;
		str2++;
	}
}