//mpicc questao3.c -o questao3
//mpirun -np 4 ./questao3

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int calculaPrimos(int n){
  int k, j, i=3, soma=2;

  for(k = 2; k < n; k++ ){
      for(j = 2; j < i; j++){
        if(i%j==0)
          break;
      }
        if(j==i){
          soma+=i;
        }
      i++;
    }
    return soma;
}


int main(int argc, char const *argv[])
{

    int num_proc, id_rank, n, soma=2, primos;

    MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&id_rank);
    
    if(id_rank!=0){
         MPI_Reduce(&primos,&soma,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); //Reduces values on all processes to a single value
        // MPI_Recv(&soma, 1, MPI_INT, (num_proc-1), 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    if(id_rank==0){
       printf("Digite o numero:\n");
       scanf("%d",&n);
       MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
       soma = calculaPrimos(n);
       //MPI_Reduce(&soma,&primos,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
       MPI_Send(&soma, 1, MPI_INT, (id_rank+1)%num_proc, 0, MPI_COMM_WORLD);
       printf("%d\n", soma);
    }
    
    MPI_Finalize();
	
    return 0;
}
