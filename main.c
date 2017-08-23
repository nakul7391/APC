/*main function for arithmatic precision calculator*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doublelink.h"
#include "operation.h"

int handle_integer(char *input, int oper, int is_float);
int handle_float(char *input, int oper);
int get_real_part(char *real, char *arg, char **dot_ptr);

/*function to return to be length of string*/
int maximize_length(int input_len);

int int_len;
int float_len;
int float_ops;
int minus;

/*for integers*/
Dlist *head_real1 = NULL, *tail_real1 = NULL;
Dlist *head_real2 = NULL, *tail_real2 = NULL;
Dlist *head_real_out = NULL, *tail_real_out = NULL;

/*for floats*/
Dlist *head_float1 = NULL, *tail_float1 = NULL;
Dlist *head_float2 = NULL, *tail_float2 = NULL;
Dlist *head_float_out = NULL, *tail_float_out = NULL;

int main(int argc, char *argv[] )
{
		char real1[1000], real2[1000], *ptr1, *ptr2;
		char *dot_ptr1, *dot_ptr2;
		int i = 0;
		/*main code*/
		#ifndef AUTOINPUT
		if( argc < 4 )
		{
			printf("Error! Invalid inputs\n");
			printf("Usage: <file.out> <operand1> <operator> <operand2>\n");
			printf("Operators: + - \"*\" /\n");
			return 1;
		}

		/*check if input is float or not in a temp*/

		if( strchr(argv[1],'.') != NULL || strchr(argv[3],'.') != NULL ) /*float */
		{
				float_ops = 1;
				/*get real and decimal parts saperate*/
				get_real_part(real1, argv[1],&dot_ptr1);
				get_real_part(real2, argv[3],&dot_ptr2);

				/*get max length for real part and create string*/
				if(real1[0] != '\0' && real2[0] != '\0' )
				{
				int_len = strlen(real1) > strlen(real2)?maximize_length(strlen(real1)):maximize_length(strlen(real2));
				handle_integer(real1,1,0);
				handle_integer(real2,2,0);
				}
				else if( real1[0] == '\0' && real2[0] == '\0')
				int_len = 0;
				else if( real1[0] == '\0')
				{
						int_len = maximize_length(strlen(real2));
						handle_integer(real1,1,0);
						handle_integer(real2,2,0);
				}
				else if( real2[0] == '\0' )
				{
					int_len = maximize_length(strlen(real1));
					handle_integer(real1,1,0);
					handle_integer(real2,2,0);
				}

				/*get max length for decimal parts and create string
				one case is not working if 123. + 123.*/
				if( dot_ptr1 != NULL  && dot_ptr2 != NULL )
				{
				float_len = strlen(dot_ptr1) > strlen(dot_ptr2)?maximize_length(strlen(dot_ptr1)):maximize_length(strlen(dot_ptr2));
				handle_integer(dot_ptr1,1,1);
				handle_integer(dot_ptr2,2,1);
				}
				else if( dot_ptr1 != NULL )
				{
				float_len = maximize_length(strlen(dot_ptr1));
				handle_integer(dot_ptr1,1,1);
				handle_integer("0",2,1);
				}
				else if( dot_ptr2 != NULL )
				{
				float_len = maximize_length(strlen(dot_ptr2));
				handle_integer("0",1,1);
				handle_integer(dot_ptr2,2,1);
				}
				else
				{
				float_len = maximize_length(1);
				handle_integer("0",1,1);
				handle_integer("0",2,1);
				}
		}
		else /*integer */
		{
				/*find largest number store its length*/
				int_len = strlen(argv[1]) > strlen(argv[3])?maximize_length(strlen(argv[1])):maximize_length(strlen(argv[3]));
				handle_integer(argv[1],1,0);
				handle_integer(argv[3],2,0);
		}

		#endif

		/*check operation and call appropriate function*/
		if( strcmp(argv[2],"+") == 0 )
		summation(float_ops);
		else if( strcmp(argv[2],"-") == 0 )
		subtraction(float_ops);
		else if( strcmp(argv[2],"*") == 0 )
		multiplication(float_ops);
		else if( strcmp(argv[2],"/") == 0 )
		division(float_ops);

		printf("ANSWER\n");
		show_output(&head_real_out, &head_float_out, float_ops, minus );

		/*delete list free heap memory*/
		delete_list(&head_real_out, &tail_real_out);
		delete_list(&head_float_out, &tail_float_out);
		return 0;
}


/*divide the string into 4 4 digits and convert it to
int and then store if int pad zeros before if float pad
Zeros after and store the length*/
int handle_integer(char *input,int oper, int is_float)
{
		int temp, i = 0;
		/*create new string*/
		if( int_len == 0 )
		int_len = 5;
		char chunk[5];
		int num = 0;

		char new_str[int_len];
		char new_str_float[float_len];

		new_str_float[0] = '\0';
		new_str[0] = '\0';

		if( is_float == 0) /*pad zeros up front*/
		{
				temp = int_len - strlen(input);
				while( temp-- )
				{
						new_str[i] = '0';
						i++;
				}
				new_str[i] = '\0';
				strcat(new_str,input);
				temp = int_len;
		}
		else /*it is float pad zeros to the end*/
		{
				strcat(new_str_float,input);
				i = strlen(new_str_float);
				while( i < float_len)
				{
				new_str_float[i] = '0';
				i++;
				}
				new_str_float[i] = '\0';
				temp = float_len;
		}

		/*store string into link list by converting into chunks*/

			i = 3;
			while( temp-- )
			{
					if( is_float == 0)
		      chunk[i] = new_str[temp];
					else
					chunk[i] = new_str_float[temp];
		      i--;
		      if( i == -1)
		      {
		          chunk[4] = '\0';
							num = atoi(chunk);
		          if( oper == 1 && is_float == 0 )
		          insert_at_first(&head_real1, &tail_real1,num);
		          else if(oper == 2 && is_float == 0 )
		          insert_at_first(&head_real2, &tail_real2,num);
							else if( oper == 1 && is_float == 1 )
		          insert_at_first(&head_float1, &tail_float1,num);
		          else if(oper == 2 && is_float == 1 )
		          insert_at_first(&head_float2, &tail_float2,num);
		          i = 3;
		      }
			}
}

/*return length in multiple of four*/
int maximize_length(int input_len)
{
		int new_str_len;

		new_str_len = input_len;

		if( input_len % 4 != 0 )
		{
			new_str_len = input_len + 4;
			while( new_str_len % 4 != 0 )
			new_str_len--;
		}

		return new_str_len;
}


int get_real_part(char *real, char *arg, char **dot_ptr)
{
		int i;
		/*get real part*/
		i = 0;
		while( arg[i] != '.' )
		{
				real[i] = arg[i];
				i++;
		}
		real[i] = '\0';

		*dot_ptr = strchr(arg,'.');

		if(  *dot_ptr  != NULL )
		*dot_ptr = *dot_ptr + 1;
		else
		*dot_ptr = NULL;

		return 1;
}
