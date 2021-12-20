#include "youthworks.h"

create_list_type(matched_pairs_t, matched_pair_t *)

matched_pairs_t *find_matching(digraph_t *pDigraph, youths_t *youths, jobs_t *jobs) {

  FILE *fDigraph = fopen("tmp.gml", "w");
  if (!fDigraph) {
    fprintf(stderr, "Failed to open tmp.gml: %s\n", strerror(errno));
    exit(1);
  }
  
  uint32_t *inverse_mapping = print_digraph(fDigraph, pDigraph, youths, jobs);
  fclose(fDigraph);
  
  char tmpstring[1024];
  snprintf(tmpstring, 1024, "matching tmp.gml > tmp.out");
  system(tmpstring); //Solve the assignment problem

  unlink("tmp.gml");
  
  FILE *fp = fopen("tmp.out", "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open tmp.out: %s\n", strerror(errno));
    exit(1);
  }

  matched_pairs_t *pairs = matched_pairs_t_alloc(10, 10);
  
  fscanf(fp, "{\n\"matching\":[");

  int64_t total_weight = 0;
  uint32_t i;
  for(i = 0; i < youths->nLength; i++) {
    matched_pair_t *pair;
    pair = malloc(1 * sizeof(matched_pair_t));
    int success = fscanf(fp, "[%d, %d, %d]", &pair->youth_id, &pair->job_id, &pair->weight);
    if(success != 3 || success == EOF) {
      free(pair);
      break;
    }
    //fprintf(stderr, "|%u -> %u|", pair->youth_id, youths->pList[inverse_mapping[pair->youth_id]]->youth_id);
    //fprintf(stderr, "|%u -> %u -> %u|", pair->job_id, inverse_mapping[pair->job_id], jobs->pList[inverse_mapping[pair->job_id]]->worksite_id);
    pair->youth_id = inverse_mapping[pair->youth_id];
    pair->job_id = inverse_mapping[pair->job_id];
    total_weight += pair->weight;

    assert(youths->pList[pair->youth_id]->in_graph);
    
    matched_pairs_t_push(pairs, pair);

    if(fscanf(fp, ",") == EOF) break;
  }
  //fprintf(stderr, "{{%u, %lld, %u, %u}}\n", pairs->nLength, total_weight, youths->nLength, jobs->nLength);

  fclose(fp);
  unlink("tmp.out");
  
  free(inverse_mapping);
  
  return pairs;
}

void matched_pairs_free(matched_pairs_t *pairs) {
  for(uint32_t i = 0; i < pairs->nLength; i++) {
    free(pairs->pList[i]);
  }
  matched_pairs_t_free(pairs);
  free(pairs);
}
