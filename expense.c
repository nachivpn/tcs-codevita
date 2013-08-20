#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BUFFER 100


#define N   0
#define I   1
#define II    2
#define III	3
#define IV	4
#define V   5
#define VI 	6
#define VII	7
#define VIII 8
#define IX   9
#define X    10
#define XI  11
#define NUM 14
#define SP 	15
#define	CH	16	
#define CR	17
#define ERR	18
#define NL  19

int state = N;

struct obj
{
    char *name;
    float spent;
    float result;

}*person;


int max_person,count_ppt,count_tran,amt_spent,array_used;
int *array;


void init_array(int num)
{
    array = (int *) malloc(10*sizeof(int));
    array[array_used] = num;
}

void addto_array(int num)
{
        if(array_used % 10 == 0)
            array = (int *) realloc(array,10*sizeof(int));
        array_used++;
        array[array_used] = num;
}


void del_array()
{
    free(array);
    array_used = 0 ;
}

void update(int count_ppt,float spent)
{
    int j;
    float share = spent/count_ppt;
    
        for(j=0;j < count_ppt;j++)
        {
            person[array[j]].result += share;
        }
    
}

void print_result()
{
    int i;
    for(i=0;i<max_person;i++)
    {
       printf("%s",person[i].name);
       person[i].result = person[i].spent - person[i].result;
       printf(" %f\n",person[i].result);
        
    }
}

void error()
{
    printf("Invalid Input\n");
	exit(0);
}

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int add_person_spent(char* str,float spent)
{
    int i;
    for(i=0;i<max_person;i++)
    {
        if(strcmp(person[i].name,str)==0)
        {
            person[i].spent=spent;
            return i;
        }
    }
}

int ret_pindex(char* str)
{
    int i;
    for(i=0;i<max_person;i++)
        if(strcmp(person[i].name,str)==0)
            return i;
}


int input()
{
    person = (struct obj*) malloc(10*sizeof(struct obj));
    char *buffer =(char*) malloc((BUFFER+1)*sizeof(char));
    int count_person = 0;
    while(fgets(buffer,BUFFER,stdin))
    {
		size_t len = strlen(buffer);
        char c;
        int prev_val = 0;
        size_t i = 0;
        char *str = (char*) malloc( 30 * (sizeof(char)) );
        count_tran=0;
        
        count_ppt=0;
        while(i<len-1)
        {
            c = buffer[i];
            
            int type,val,ascii_val = (int)c;
            
            if(ascii_val>=48 && ascii_val<=57)
    	    {
			    val = ascii_val - 48;
			    type = NUM;
		    }
		    else if((ascii_val>=65 && ascii_val<=90) || (ascii_val>=97 && ascii_val <=122))
			    type = CH;
		    else if(ascii_val ==13)
			    type = CR;
            else if(ascii_val ==10)
                type = NL;
            else if(ascii_val == 32)
                type = SP;
		    else
			    type = ERR;
                
            switch(type)
            {
                case CH:
                {
                    if(state == N)
                    {
                        append(str,c);
                        state = II;
                    }
                    else if(state == I)
                    {
                        str = malloc( 30 * (sizeof(char)) );
                        append(str,c);
                        state = II;
                    }
                    else if(state == II)
                    {
                        append(str,c);
                        state = II;
                    }
                    else if(state == V)
                    {
                        str = malloc( 30 * (sizeof(char)) );
                        append(str,c);
                        state = VI;
                    }
                    else if(state == VI)
                    {
                        append(str,c);
                        state = VI;
                    }
                    else if(state == IX)
                    {
                        str = malloc( 30 * (sizeof(char)) );
                        append(str,c);
                        state = X;
                    }
                    else if(state == X)
                    {
                        append(str,c);
                        state = X;
                    }
                    else if(state == XI)
                    {
                        del_array();
                        str = malloc( 30 * (sizeof(char)) );
                        append(str,c);
                        state = VI;
                    }
                    break;
                }
                case SP:
                {
                    if(state == II)
                    {
                        if(count_person % 10 == 0)
                            person = (struct obj *) realloc(person,10*sizeof(struct obj));
                        state = I;
                        person[count_person].name = strdup(str);
                        person[count_person].result = 0;
                        count_person++;
                    }
                    else if(state == VI)
                       state = VII;   
                    else if(state == VIII) 
                    {
                        init_array(add_person_spent(str,(float)prev_val));
                        amt_spent = prev_val;
                        prev_val = 0;
                        state = IX;
                    }
                    else if(state == X)
                    {
                        addto_array(ret_pindex(str));
                        count_ppt++;
                        state = IX;
                    }
                    break;
                }
                case CR:
                {
                    if(state == II)
                    {
                        person[count_person].name = strdup(str);
                        person[count_person].result = 0;                    
                        state = III;
                    }
                    else if(state == IV)
                    {
                        if(prev_val != count_person+1)
                            error();
                        else
                            max_person = prev_val;
                        prev_val = 0;
                        state = V;
                    }
                    else if(state == X)
                    {
                        addto_array(ret_pindex(str));
                        count_ppt++;
                        update(count_ppt+1,(float)amt_spent);
                        amt_spent = 0;
                        count_ppt = 0;
                        state = XI;
                    }
                    
                    break;
                    
                }
                case NL:
                {
                    break;
                }
                case NUM:
                {
                   if(state == III)
                   {
                       prev_val=val;
                       state = IV;
                   }
                   else if(state == IV) 
                   {
                       prev_val = prev_val*10 + val;
                       state = IV;
                    }
                    else if(state == VII)
                    {
                        prev_val=val;
                        state = VIII;
                    }
                    else if(state == VIII) 
                   {
                       prev_val = prev_val*10 + val;
                       state = VIII;
                    }
                   break;
                }
                case ERR:
                {
                    error();
                }
            }
            
            i++;
        }
	}
    
}

int main()
{
    
    input();
    print_result();
    free(person);
    return 0;
}
