#include<stdio.h>
#include<stdlib.h>

float* arr;
float BR;


int input()
{
	arr = malloc(4 * sizeof(float));
	int i=0;
	while(	scanf("%f", &arr[i]) == 1 && i<4 ) 
		i++;
	if(i<4)
		return -1;
	else 
		return 1;
}

float brokerage(int a)
{
	return ((float)a*(BR/100));
}

float servicetax(float a)
{
	return ((float) a)* 0.1036;
}

float stt(int a)
{
	return (0.00025)*a;
}
	
int main()
{
	float BA,SA,Q,TBA,TSA,BR_b,BR_s,ST,STT,T_b,T_s,X,P,BP,profit;
	if(input()==1)
	{
		BR = arr[0];
		BA = arr[1];
		SA = arr[2];
		Q = arr[3];
		TBA = BA * Q;
		TSA = SA * Q;
		BR_b = brokerage(TBA);
		BR_s = brokerage(TSA);
		ST = servicetax(BR_b);
		STT = stt(TSA);
		T_b = BR_b + ST;
		T_s = BR_s + STT + ST;
		X = T_b + T_s;
		P = X + (TBA+TSA) *(0.006/100);
		BP = TSA - TBA;
		profit = BP - P;
		if(profit > 0)
			printf("Profit\n%f",profit);
		else
			printf("Loss\n%f",profit*-1); 
	}
	else
		printf("Invalid Input");

	free(arr);
	return 1;
}	
