#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

#include "youthworks.h"

int main(int argc, char **argv) {
  struct timeval tv1;
  struct timezone tzp1;
  gettimeofday(&tv1, &tzp1);
  uint32_t random_seed = ((tv1.tv_sec & 0177) * 1000000) + tv1.tv_usec;
  
  fprintf(stderr, "random seed = %d\n", random_seed);
  srand(random_seed);
  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <youth>.csv <jobs>.csv \n", argv[0]);
    exit(0);
  }

  csv_data *pYouthCSV = csv_read_file(argv[1]);
  //write_csv(stdout, pYouthCSV);
  youths_t *youths = create_youth_list(pYouthCSV);
  csv_data_free(pYouthCSV);

  csv_data *pJobsCSV = csv_read_file(argv[2]);
  //write_csv(stdout, pJobsCSV);
  jobs_t *jobs = create_job_list(pJobsCSV);
  csv_data_free(pJobsCSV);

 
  uint8_t use_soft_constraints = 1;
  digraph_t *pDigraph = create_digraph(youths, jobs, use_soft_constraints);

  matched_pairs_t *pairs = find_matching(pDigraph, youths, jobs);
  digraph_free(pDigraph);

  create_workbook(pairs, youths, jobs);  
  matched_pairs_free(pairs);
  
  free_youth_list(youths);
  free_job_list(jobs);

  return 0;
  
}
