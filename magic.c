#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 20
#define NOT_INT 0
#define DONE 2
#define COLUM_TURN 1
#define SECOND_DIAG 1
#define ERROR 0 
#define NOT_MAGIC 0
#define STOP 0
#define DEF_VAL 1

void welcome();
int * getMatrix();
int printMatrix(int *magic_matrix);
int getMagicSum(int *magic_matrix);
int magicVerticalSumTest(int *magic_matrix, int magic_sum);
int magicDiagSumTest(int *magic_matrix, int magic_sum);
void success();


/* 
MAMAN 12 
Shimon Port

This app tells you if your numbers create a magic matrix. The app recives integers from user and prints the matrix if the proper values are inserted, if not it will stop and show an error mesage. If the values are proper but dont make a magic matrix then the user will see the matrix creataed with a mesage indicting the problom. 
The rules for magic matrix is that the matrix is a square NxN, the numbers are between 1-N^2 and each row, colum and diagnal sum up to same value.
*/

int main()
{
	int *magic_matrix;
	int magic_sum;

	/* Welcome mesage */
	welcome();

	/* Reccive and asure propper input */
	if((magic_matrix = getMatrix()) == ERROR)
		return ERROR;

	/* print matrix */
	if((printMatrix(magic_matrix)) == NOT_MAGIC)
		return STOP;

	/* Get the matrix's magic sum value */
	magic_sum = getMagicSum(magic_matrix);

	/* Check proper magic sum value for rows and then colums in matrix */
	if(magicVerticalSumTest(magic_matrix, magic_sum) == NOT_MAGIC)
		return STOP;

	/* Check proper magic sum value for all diagnals in matrix */
	if(magicDiagSumTest(magic_matrix, magic_sum) == NOT_MAGIC)
		return STOP;
	
	/* Reaching this point means we have a magic matrix --> print success mesage */
	success();
	return DEF_VAL;
}

/* Welcome mesage */
void welcome()
{
	printf("Hello, insert %d numbers of type integers to check if your numbers create a magic matrix.\n" , N * N);
}


/* Reccive and asure propper input */
int * getMatrix()
{
	int *magic_matrix;
	int cur_type = 0, i = 0, input_values = 0;

	magic_matrix = malloc(N * N * sizeof(int));

	while((cur_type = scanf("%d", magic_matrix + i)) != EOF)
	{		
		input_values++; /* Counter for amount of values inserted */
		i++;

		if(cur_type == NOT_INT)
		{
			printf("The matrix accepts only integers, try again!\n");
			return ERROR;
		}

		if(input_values > N*N)
		{
			printf("To many values, try again!\n");
			return ERROR;
		}
	}

	if(input_values < N*N)
	{
		printf("Missing %d values, try again!\n", N*N - input_values);
		return ERROR;
	}
	
	return magic_matrix;
}

	
/* print matrix */
int printMatrix(int *magic_matrix)
{
	int i, j, cur_location, cur_val;
	bool magic_value = true;

	printf("\n"); /* For proper output in case of one line input from terminal */
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			cur_location = i * N + j;
			printf("%d\t", *(magic_matrix + cur_location));
			cur_val = *(magic_matrix + cur_location);
			if(cur_val < 1 || cur_val > N * N)
				magic_value = false;
		}
		printf("\n");
	}

	if(!magic_value)
	{
		printf("False value insert.\nValues need to be between 1-%d, try again!\n", N*N);
		return NOT_MAGIC;
	}

	return DEF_VAL;
}

/* Check magic sum value */
int getMagicSum(int *magic_matrix)
{
	int i, magic_sum = 0;

	for(i = 0; i < N; i++)
		magic_sum+= *(magic_matrix + i);
			
	return magic_sum;
}


/* Check proper magic value for rows and then colums in matrix */
int magicVerticalSumTest(int *magic_matrix, int magic_sum)
{
	int colum_test = 0, combined_val, i, j, cur_location;

	while(colum_test != DONE)
	{
		for(i = 0; i < N; i++)
		{
			combined_val = 0 ; /* row or colum */

			for(j = 0; j < N; j++)
			{
				if(colum_test == COLUM_TURN)
					cur_location = i + N * j;
				else
					cur_location = i * N + j; 

				combined_val+= *(magic_matrix + cur_location);
			}
		
			if(combined_val != magic_sum)
			{
				printf("The matrix is not a basic magic matrix.\n");
				printf("Row or colum value is %d while magic value is %d!\n", combined_val, magic_sum);
				return NOT_MAGIC;
			}
		}
		colum_test++;
	}
	
	return DEF_VAL;
}
	

/* check proper magic value for all diagnals in matrix */
int magicDiagSumTest(int *magic_matrix, int magic_sum)
{
	int diag_test = 0, i = 0, diag_val, j, cur_location;
	while(diag_test != DONE)
	{
		diag_val = 0;

		if(diag_test == SECOND_DIAG) /* right top corner to bottom left corner */
			 j = N - 1;
		else
			j = 0;

		for(i = 0; i < N; i++)
		{
			cur_location = i * N + j;
			diag_val+= *(magic_matrix + cur_location);

			if(diag_test == SECOND_DIAG)
				j--;
			else
				j++;
		}
		if(diag_val != magic_sum)
		{
			printf("The matrix is not a basic magic matrix.\n");
			printf("Diagnal value is %d while magic value is %d!\n", diag_val, magic_sum);
			return NOT_MAGIC;
		}
		diag_test++;
	}
	
	return DEF_VAL;
}

/* success mesage */
void success()
{
	printf("Success! The matrix is a basic magic matrix!\n");
}
