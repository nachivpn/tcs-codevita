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

int main()
{
	FILE *fp;
	fp=fopen("file_sort.t","r");
	int VAL,input_type,prev_val;
	int curr_state = N;	
	char ch = getc(fp);
	while( !feof(fp) )
	{
		int ascii_val = (int)ch;
		if(ascii_val>=48 && ascii_val<=57)
		{
			VAL = ascii_val - 48;			
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
				else if(curr_state == III)
				{
					curr_state=I;
					prev_val=VAL;
				}
				break;
			}
			case COM :
			{
				if(curr_state == N)
				{	
					printf("\nError1");
					break;
				}
				else if(curr_state == I)
				{
					printf("\n%d",prev_val);
					curr_state=III;
					prev_val=0;
				}	
				else if(curr_state == III)
				{
					printf("\nError2");
					break;
				}
				break;
			}
			case CR :
			{
				if(curr_state == N)
				{	
					printf("\nError3");
					break;
				}
				else if(curr_state == I)
				{
					printf("\n%d\nComplete",prev_val);
					break;
				}	
				else if(curr_state == III)
				{
					printf("\nError4");
					break;
				}
				break;
			}
			case ERR:
			{					
				printf("\nError : Invalid character");				
				exit(0);
			}				
		}
		ch=getc(fp);
	}	
	fclose(fp);
	
	return 1;
}	

