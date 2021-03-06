/*
	Problem statement : Parse a file with numbers separated by commas and sort them
	Design :
		- Parses the input file using FSM simulation
		- Stores the numbers in dynamic floating point array
		- Uses Quicksort to sort the floating point array

*/
#include<stdio.h>
#include<stdlib.h>

/*states*/
#define N 	0
#define I 	1
#define II	2
#define III	3
#define M	10
#define P	11

/*Input Types*/
#define NUM	4
#define COM	5
#define	DOT	6	
#define CR	7
#define ERR	8
#define NEG	9

float* arr;
int used=0;

void display(int i,int max)
{
	for(i;i<max;i++)	
		(i==0)?printf("%f",arr[i]):printf(",%f",arr[i]);
	printf("\n");
}

void rev_display(int i,int end)
{	
	int j;
	for(j=i-1;j>=end;j--)	
		(j==i-1)?printf("%f",arr[j]):printf(",%f",arr[j]);
	printf("\n");
}

void quicksort(float *array,int p, int r)
{
	if(p<r)
	{
		int q = partition(array,p,r);
		quicksort(array,p,q-1);
		quicksort(array,q+1,r);
	}
	//display();
}

int partition(float *array,int p,int r)
{
	float x=array[r];
	int j,i=p-1;
	for(j=p;j<=r-1;j++)
	{
		if(array[j]<=x)
		{
			i++;
			float temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	float temp_1 = array[i+1];
	array[i+1] = array[r];
	array[r] = temp_1;
	return i+1;
}


void error()
{
	printf("Invalid Input\n");
	exit(0);
}

void insert(float value)	
{
	arr[used]=value;
	used++;
	arr=(float*) realloc(arr,sizeof(float));
}

void FSM_simulate()
{
	arr = (float*) malloc(sizeof(float));	
	FILE *fp;
	fp=fopen("test_file_sort","r");
	if(fp == NULL)
		exit(0);
	int input_type,sign=P;
	int prev_val,VAL;
	float prev_dval,dec_denom=1;
	int curr_state = N;	
	char ch = getc(fp);
	while( !feof(fp) )
	{
		int ascii_val = (int)ch;
		if(ascii_val>=48 && ascii_val<=57)
		{
			VAL = (float)ascii_val - 48;			
			input_type = NUM;
		}
		else if(ascii_val==44)
			input_type = COM;
		else if(ascii_val==46)
			input_type = DOT;
		else if(ascii_val==10)
			input_type = CR;
		else if(ascii_val==45)
			input_type = NEG;
		else
			input_type = ERR;
		switch(input_type)
		{
			case NUM :
			{
				if(curr_state == N)
				{
					curr_state=I;
					prev_val=VAL;
				}
				else if(curr_state == I)
				{
					curr_state=I;
					prev_val=prev_val*10+VAL;
				}
				else if(curr_state == II)
				{
					dec_denom*=10;					
					curr_state=II;
					prev_dval=prev_dval+(VAL/dec_denom);
				}
				else if(curr_state == III)
				{
					curr_state=I;
					prev_val=VAL;
				}
				break;
			}
			case DOT:
			{
				if(curr_state == I)
				{
					curr_state=II;
					prev_dval=(float)prev_val;
				}
				else 
					error();
					
				break;
			}
			case COM :
			{
				if(curr_state == I)
				{
					(sign==M)?insert((float)prev_val*-1):insert((float)prev_val);
					curr_state=III;
					prev_val=0;
					sign=P;
				}
				else if(curr_state == II)
				{
					(sign==M)?insert(prev_dval*-1):insert(prev_dval);
					curr_state=III;
					prev_dval=0;
					dec_denom=1;
					sign=P;
				}	
				else 
					error();
				break;
			}
			case NEG:
			{
				if(curr_state == N || curr_state == III)
				{
					sign = M;
				}
				else 
					error();
				break;
			}
			case CR :
			{
				if(curr_state == I)
				{
					(sign==M)?insert((float)prev_val*-1):insert((float)prev_val);
					break;
				}
				else if(curr_state == II)
				{
					(sign==M)?insert(prev_dval*-1):insert(prev_dval);
					break;
				}	
				else 
					error();
				break;
			}
			case ERR:
				error();				
		}
		ch=getc(fp);
	}	
	fclose(fp);
}

int main()
{
	FSM_simulate();
	printf("Originial array :\n");
	display(0,used);
	printf("Array sorted in ascending order :\n");
	quicksort(arr,0,used-1);
	display(0,used);
	printf("Array sorted in descending order :\n");
	rev_display(used,0);	
	free(arr);
	return 1;
}	
