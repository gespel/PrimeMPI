#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_rank == 0) {
        long buf[2];
        FILE *fp;
        fp = fopen("primes.txt", "w+");
        while(1) {
            MPI_Recv(buf, 2, MPI_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("prime was found: %ld (thread %ld)\n", buf[0], buf[1]);
            fprintf(fp, "%ld\n", buf[0]);
        }
    }
    else {
        long buf[2];
        buf[1] = world_rank;
        for(long i = (world_rank+1); i > -1; i += (world_size-1)) {
            for(long j = 2; j <= i; j++) {
                if(i % j == 0) {
                    if(i == j) {
                        buf[0] = i;
                        MPI_Send(buf, 2, MPI_LONG, 0, 0, MPI_COMM_WORLD);
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}
