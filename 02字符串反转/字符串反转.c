#include<stdio.h>
#include<string.h>

void StrReversal(char *str);
int main()
{
	char str[]="abcdefgh";

	StrReversal(str);

	printf("%s\n",str);
	return 0;
}
void StrReversal(char *str)
{
	char *begin = str;
	char *end = str+strlen(str)-1;

	while (begin < end)
	{
		*begin = *begin ^ *end;
		*end = *begin ^ *end;
		*begin = *begin ^ *end;
		begin++;
		end--;
	}
}