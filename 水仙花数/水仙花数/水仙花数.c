#include<stdio.h>

int main()
{
	int i;
	int ge;
	int shi;
	int bai;

	for ( i = 100; i <1000; i++)
	{
		ge=i%10;
		shi=i/10%10;
		bai=i/100;
		if(ge*ge*ge+shi*shi*shi+bai*bai*bai==i)
		{
			printf("%d\n",i);
		}
	}

	return 0;
}