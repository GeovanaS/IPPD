#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void){
    int my_rank,num_proc,proc_rank,cont=0;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    
    proc_rank = (num_proc + 1) % 2;
    while(cont != 10){
      if(my_rank!=0){
         cont++;
         printf("Processo %d está passando a bola para o processo %d\n",my_rank,proc_rank);
         MPI_Send(&cont,1,MPI_INT,proc_rank,0,MPI_COMM_WORLD);
       }else{
      	 printf("Processo %d está recebendo a bola do processo %d\n",my_rank,proc_rank);
      	 //for(int i=1;i<num_proc;++i){
      	 MPI_Recv(&cont,1,MPI_INT,my_rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      	 //}
      }
    }
    MPI_Finalize(); 
	return 0;
}