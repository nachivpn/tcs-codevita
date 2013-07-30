/*Parse a file with numbers separated by commas and sort them*/
#include<stdio.h>
#include<stdlib.h>

/*states*/
#define N 	0
#define I 	1
#define II	2
#define III	3

/*Input Types*/
#define NUM	4
#define COM	5
#define	DOT	6	
#define CR	7
#define ERR	8

float* arr;
int used=0;

void error()
{
	printf("\nInvalid Input\n");
	exit(0);
}

void insert(float value)	
{
	arr[used]=value;
	used++;
	arr=(float*) realloc(arr,sizeof(float));
}

void display()
{
	int i;
	for(i=0;i<used;i++)	
		(i==0)?printf("%f",arr[i]):printf(",%f",arr[i]);
}

int main()
{
	arr = (float*) malloc(sizeof(float));	
	FILE *fp;
	fp=fopen("test_file_sort","r");
	if(fp == NULL)
		exit(0);
	int input_type,dec_pos;
	int prev_val,VAL;
	float prev_dval,dec_denom;
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
					dec_pos++;
					dec_denom=dec_pos*10;					
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
				if(curr_state == N)
				{
					error();
					break;
				}
				else if(curr_state == I)
				{
					dec_pos=0;					
					curr_state=II;
					prev_dval=(float)prev_val;
				}
				else if(curr_state == II)
				{
					error();
					break;
				}
				else if(curr_state == III)
				{
					error();
					break;
				}
					
				break;
				break;
			}
			case COM :
			{
				if(curr_state == N)
				{	
					error();
					break;
				}
				else if(curr_state == I)
				{
					insert((float)prev_val);
					curr_state=III;
					prev_val=0;
				}
				else if(curr_state == II)
				{
					insert(prev_dval);
					curr_state=III;
					prev_dval=0;
				}	
				else if(curr_state == III)
				{
					error();
					break;
				}
				break;
			}
			case CR :
			{
				if(curr_state == N)
				{	
					error();
					break;
				}
				else if(curr_state == I)
				{
					//printf("%d\nComplete",prev_val);
					insert((float)prev_val);
					break;
				}
				else if(curr_state == II)
				{
					//printf("%f\nComplete",prev_dval);
					insert(prev_dval);
					break;
				}	
				else if(curr_state == III)
				{
					error();
					break;
				}
				break;
			}
			case ERR:
				error();				
		}
		ch=getc(fp);
	}	
	fclose(fp);
	display();	
	free(arr);
	return 1;
}	

