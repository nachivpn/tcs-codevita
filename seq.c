#include<stdio.h>
#include<stdlib.h>

int *num;
int len,start=0,end=0;

void input_scan()
{
	scanf("%d", &len);
	num = (int *)malloc((len+1)*sizeof(int));
	int k,curr_start=0;
	num[len]=0;
	for(k=0;k<=len;k++)
	{
		scanf("%d",&num[k]);
		if( k!=0 && num[k] < num[k-1])
		{
			if((k-1)-curr_start > end-start )
			{
				start = curr_start;
				end = k-1;
				curr_start=k;
			}
			else
			{
				curr_start = k;
			}
		}
	}

}

void print()
{
	int i;
	for(i=start;i<=end;i++)
		printf("%d ",num[i]);
}

int main()
{
	input_scan();
	print();
	return 1;
}


	
