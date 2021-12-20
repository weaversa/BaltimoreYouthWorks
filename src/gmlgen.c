#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>

#include <assert.h>

int main(int argc, char **argv) {
  uint32_t nNumNodes1 = 9000;
  uint32_t nNumNodes2 = 20000;
  uint32_t nEdgesPerNode = 500;

  assert(nNumNodes1 <= nNumNodes2);

  struct timeval tv1;
  struct timezone tzp1;
  gettimeofday(&tv1, &tzp1);
  uint32_t random_seed = ((tv1.tv_sec & 0177) * 1000000) + tv1.tv_usec;

  fprintf(stderr, "random seed = %d\n", random_seed);
  srand(random_seed);
  
  fprintf(stdout, "graph [\n  directed 1\n");
  
  uint32_t i, j;
  for(i = 0; i < nNumNodes1 + nNumNodes2; i++)
    fprintf(stdout, "  node [ id %u ]\n", i);

  for(i = 0; i < nNumNodes1; i++) {
    for(j = 0; j < nEdgesPerNode; j++) {
      uint32_t nNode2 = (rand() % nNumNodes2) + nNumNodes1;
      uint32_t nWeight = (rand() % 1000) + 1;
      fprintf(stdout, "  edge [ source %u, target %u, label \"%u\" ]\n",
              i, nNode2, nWeight);
    }
  }
  fprintf(stdout, "]\n");

  return 0;
  
}
