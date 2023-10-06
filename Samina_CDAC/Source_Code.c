#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#pragma comment (lib, "msmpi.lib")


	
int main(int argc, char **argv)
{
	int size, block_size;
	printf("\nEnter the size of matrix\n");
	scanf("%d",&size);	
	printf("\nEnter the size of block\n");
	scanf("%d",&block_size);	
	int A[size][size],B[size][size],C[size][size],CC[size][size],BT[size][size];
	
	for (int i = 0; i < size; i++)
	{
		
		for (int j = 0; j < size; j++)
		{
			A[i][j] = (rand()%5);
			B[i][j] = (rand()%5);
			C[i][j] = 0;
			CC[i][j] = 0;
		}
	}
	/*printf("\nMatrix A :\n");
	for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("%d ",A[i][j]);
			}
			printf("\n");
		}
	printf("\nMatrix B :\n");
	for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("%d ",B[i][j]);
			}
			printf("\n");
		}*/
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			BT[i][j] = B[j][i];
		}
	}

	
	int i = 0, j = 0, k = 0, jj = 0, kk = 0;	
		
		//serial
		clock_t t1,t2;
		printf("\n\nComputation has begun(Serial block)\n");
		t1= clock();
		
		for (jj = 0; jj < size; jj += block_size)
			{
				
				for (kk = 0; kk < size; kk += block_size)
				{
					
					for (i = 0; i < size; i++)
					{
						for (j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
						{
							int tmp = 0;
							for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
							{
								tmp += A[i][k] * B[k][j];
							}
							C[i][j] += tmp;
						}
					}
				}
			}
		t2= clock();
		
		/*for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("%d ",C[i][j]);
			}
			printf("\n");
		}*/
		printf("time taken by serial computing %f\n",((float)(t2-t1)/CLOCKS_PER_SEC));
		
		for ( i = 0; i < size; i++)
		{
			
			for ( j = 0; j < size; j++)
			{
				
				C[i][j] = 0;
				CC[i][j] = 0;
			}
		}
		//parallel block
		printf("\n\nComputation has begun(parallel block)\n");
		t1= clock();
		int tmp;
		int chunk = 1;
		int tid;
		omp_set_num_threads(4);
		#pragma omp parallel shared(A, B, C, size, chunk) private(i, j, k, jj, kk, tid, tmp)
		{
			//omp_set_dynamic(0);
			
			
			#pragma omp for schedule (static, chunk) 
			for (jj = 0; jj < size; jj += block_size)
			{
				
				for (kk = 0; kk < size; kk += block_size)
				{
					
					for (i = 0; i < size; i++)
					{
						for (j = jj; j < ((jj + block_size) > size ? size : (jj + block_size)); j++)
						{
							tmp = 0;
							for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)
							{
								tmp += A[i][k] * B[k][j];
							}
							C[i][j] += tmp;
						}
					}
				}
			}
		}
		t2= clock();
		/*for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("%d ",C[i][j]);
			}
			printf("\n");
		}*/
		printf("time taken by parallel block computing %f\n",((float)(t2-t1)/CLOCKS_PER_SEC));
		
	
	return 0;
}

/* Output:

*/

