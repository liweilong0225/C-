#include<stdio.h>

int BinaryFind(int arr[],int len,int n);
int main()
{
	int arr[11] = {1,2,3,4,5,6,7,8,9,10,11};

	printf("%d\n",BinaryFind(arr,11,11));
	return 0;
}

int BinaryFind(int arr[],int len,int n)
{
	int begin = 0;
	int end = len -1;
	int mid = (begin+end)/2;

	while (begin <= end)
	{
		mid = (begin+end)/2;
		if (arr[mid] < n)
		{
			begin = mid + 1;
		}
		else if(arr[mid] > n)
		{
			end = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}