#ifndef MATCHING_H
#define MATCHING_H

#include "youthworks.h"

typedef struct matched_pair_t {
  uint32_t youth_id;
  uint32_t job_id;
  int32_t weight;
} matched_pair_t;

create_list_headers(matched_pairs_t, matched_pair_t *)

matched_pairs_t *find_matching(digraph_t *pDigraph, youths_t *youths, jobs_t *jobs);
void matched_pairs_free(matched_pairs_t *pairs);

#endif
