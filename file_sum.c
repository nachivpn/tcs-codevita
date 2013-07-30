/*Computes the sum of integers stored in a file in the following format
FILE:
*number of integers = n*
*integer 1*
*integer 2*
...
*integer n*
*/
#include<stdio.h>
int main()
{
	FILE *f1;
	f1=fopen("test_file_sum","r");
	if(f1!=NULL)
	{
		int n,i;
		int sum=0;
		fscanf(f1,"%d",&n);
		
		while(n!=0)
		{		
			fscanf(f1,"%d",&i);
			sum+=i;
			n--;
		}
		printf("%d\n",sum);
	}
	else 
		printf("error");
	fclose(f1);
	return 1;
}
