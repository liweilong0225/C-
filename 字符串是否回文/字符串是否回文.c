#include<stdio.h>
#include<string.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

int Palindrome(char *str);
int main()
{
	char str[]="abcdefedcba";

	if (Palindrome(str))
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
	return 0;
}

int Palindrome(char *str)
{
	char *begin = str;
	char *end = str + strlen(str) - 1;
	while (begin < end)
	{
		if (*begin == *end)
		{
			begin++;
			end--;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}