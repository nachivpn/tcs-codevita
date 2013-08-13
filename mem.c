#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Input states*/

#define N 	0
#define I 	1
#define II	2
#define III	3
#define IV	10

/*Input Types*/
#define NUM	4
#define COM	5
#define	CH	6	
#define CR	7
#define ERR	8

/*Memory count states*/
#define F 0
#define NF 1


int used=1;

struct object
{
	int offset;
	int size;
	char status;
}table[100];

void makeobj(int index,int offset, int size, char status)
{
	struct object a;
	a.offset = offset;
	a.size = size;
	a.status = status;
	table[index]=a;
	used++;
	
}

void display()
{
	int i=1;
	for(i;i<used;i++)	
		printf("%d %d %c\n",table[i].offset,table[i].size,table[i].status);
}

void error()
{
	printf("Invalid Input\n");
	exit(0);
}


void FSM_simulate(char *str)
{
	FILE *fp;
	fp=fopen(str,"r");
	if(fp == NULL)
		exit(0);
	int input_type;
	int prev_val=0,val,index,offset,size;
	int curr_state = N;	
	char ch = getc(fp),flag;
	while( !feof(fp) )
	{
		int ascii_val = (int)ch;
		if(ascii_val>=48 && ascii_val<=57)
		{
			val = ascii_val - 48;			
			input_type = NUM;
		}
		else if(ch == 'Y' || ch== 'N')
			input_type = CH;
		else if(ascii_val==44)
			input_type = COM;
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
					curr_state = N;
					prev_val = prev_val*10 + val;
				}
				else if(curr_state == I)
				{
					curr_state = I;
					prev_val = prev_val*10 + val;
				}
				else if(curr_state == II)
				{
					curr_state = II;
					prev_val = prev_val*10 + val;
				}
				break;
			}
			case COM :
			{
				if(curr_state == N)
				{
					curr_state = I;
					index = prev_val;
					prev_val =0;
				}
				else if(curr_state == I)
				{
					curr_state = II;
					offset = prev_val;
					prev_val =0;
				}
				else if(curr_state == II)
				{
					curr_state = III;
					size = prev_val;
					prev_val =0;
				}
				else
					error();
				break;
			}
			case CH:
			{
				if(curr_state == III )
				{
					curr_state = IV;
					flag = ch;
				}
				else
					error();
				break;
			}
			case CR :
			{
				if(curr_state == IV)
				{
					makeobj(index,offset,size,flag);
					curr_state = N;
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

int count(int req_mem)
{
	int i,index,curr_state,free_mem=0;
	for(i=1;i<used;i++)
	{
		if(table[i].status == 'Y')
		{
			if(curr_state == F)
				free_mem+=table[i].size;
			else if (curr_state == NF)
			{
				curr_state = F;				
				index = i;
				free_mem+=table[i].size;
			}
			if(req_mem <= free_mem)
				return index;
		}
		else 
				curr_state = NF;
	}
	return -1;
}		
		
int main()
{
	int num;
	FSM_simulate("input.txt");	
	scanf("%d",&num);
	int i=count(num);
	if(i!=-1)
		printf("%d",i);
	else
		printf("Can not be inserted");	
	return 1;
}	
