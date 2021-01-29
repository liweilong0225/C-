#include<stdio.h>

int main()
{
	int arr[10]={0,1,4,2,5,8,7,9,6,3};
	int i,j,k;
	int pTemp;
	int count = 0;
	int flag = 1;

	for (j = 0; j < 10-1; j++)
	{
		flag = 1;
		for (i = 0; i < 10-1-j; i++)
		{
			if (arr[i] > arr[i+1])
			{
				pTemp = arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=pTemp;
				count++;
			}
			flag = 0;
		}
		if (1 == flag)
		{
			break;
		}
	}

	for (k = 0; k < 10; k++)
	{
		printf("%d ",arr[k]);
	}
	printf("\n%d\n",count);
	return 0;
}