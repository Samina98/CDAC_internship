// OpenMP program to print Hello World 
// using C language 
  
// OpenMP header 
#include <omp.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
 	int nthreads,no;
       nthreads=atoi(argv[1]);
	omp_set_num_threads(nthreads);
	int s=50,i;
	int n=omp_get_num_threads();
	printf("master thread is %d\n no. of threads outside pragma=%d\n",omp_get_thread_num(),n);
        
    #pragma omp parallel for lastprivate(s,no)
     for(i=0;i<16;i++)
        {
        	no=omp_get_thread_num();
        	printf("thread no. = %d,  total thread number=%d\n",no,omp_get_num_threads()); 
               s=s+1;
               printf("sum inside the thread %d is ==%d\n \n",no,s);
        }
        
   
    // Ending of parallel region 
    printf("\nthread outside the parallel region is %d,\nresultant sum=%d\nthread for which lastprivate works=%d\n",omp_get_thread_num(),s,no);
} 

