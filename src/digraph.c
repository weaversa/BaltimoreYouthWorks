#include "youthworks.h"

create_list_type(edges_t, edge_t *)

uint8_t reduce_zip(uint16_t zip) {
  if(zip == 21201) return 0;
  if(zip == 21202) return 1;
  if(zip == 21203) return 2;
  if(zip == 21205) return 3;
  if(zip == 21206) return 4;
  if(zip == 21207) return 5;
  if(zip == 21208) return 6;
  if(zip == 21209) return 7;
  if(zip == 21210) return 8;
  if(zip == 21211) return 9;
  if(zip == 21212) return 10;
  if(zip == 21213) return 11;
  if(zip == 21214) return 12;
  if(zip == 21215) return 13;
  if(zip == 21216) return 14;
  if(zip == 21217) return 15;
  if(zip == 21218) return 16;
  if(zip == 21222) return 17;
  if(zip == 21223) return 18;
  if(zip == 21224) return 19;
  if(zip == 21225) return 20;
  if(zip == 21226) return 21;
  if(zip == 21227) return 22;
  if(zip == 21228) return 23;
  if(zip == 21229) return 24;
  if(zip == 21230) return 25;
  if(zip == 21231) return 26;
  if(zip == 21233) return 27;
  if(zip == 21234) return 28;
  if(zip == 21236) return 29;
  if(zip == 21237) return 30;
  if(zip == 21239) return 31;
  if(zip == 21251) return 32;
  if(zip == 21270) return 33;
  if(zip == 21281) return 34;
  if(zip == 21287) return 35;
  return 255;
}

uint8_t zip[36][36] = {
  {0,1,2,2,3,3,3,2,2,1,2,2,2,2,2,1,1,4,1,3,2,3,2,3,2,1,2,2,3,4,3,2,2,3,4,3},
  {1,0,1,1,2,4,4,3,2,2,2,1,2,3,3,2,1,3,2,2,3,4,3,4,3,2,1,1,3,3,2,2,2,4,3,2},
  {2,1,0,2,3,5,5,4,3,3,3,2,3,4,4,3,2,4,3,3,4,5,4,5,4,3,2,2,4,4,3,3,3,5,4,3},
  {2,1,2,0,1,5,5,4,3,3,3,1,2,4,4,3,2,2,3,1,4,5,4,5,4,3,1,2,3,2,1,3,3,5,2,1},
  {3,2,3,1,0,5,5,4,3,3,3,1,1,4,4,3,2,3,4,2,5,6,5,6,5,4,2,3,2,1,1,2,2,5,3,2},
  {3,4,5,5,5,0,2,2,3,2,4,4,4,1,1,2,3,6,2,5,3,4,2,2,1,2,4,3,5,6,6,4,4,2,6,4},
  {3,4,5,5,5,2,0,1,2,2,3,4,4,1,2,2,3,7,3,6,5,6,4,4,3,4,5,5,5,6,6,4,4,2,7,6},
  {2,3,4,4,4,2,1,0,1,1,2,3,3,1,2,2,2,6,3,5,4,5,4,4,3,3,4,4,4,5,5,3,3,2,6,5},
  {2,2,3,3,3,3,2,1,0,1,1,2,2,2,3,2,1,5,3,4,4,5,4,5,4,3,3,3,3,4,4,2,2,3,5,4},
  {1,2,3,3,3,2,2,1,1,0,2,2,2,1,2,1,1,5,2,4,3,4,3,4,3,2,3,3,3,4,4,2,2,2,5,4},
  {2,2,3,3,3,4,3,2,1,2,0,2,2,3,3,2,1,5,3,4,4,5,4,5,4,3,3,3,2,3,4,1,2,4,5,4},
  {2,1,2,1,1,4,4,3,2,2,2,0,1,3,3,2,1,3,3,2,4,5,4,5,4,3,2,2,2,2,2,2,2,4,3,2},
  {2,2,3,2,1,4,4,3,2,2,2,1,0,3,3,2,1,4,3,3,4,5,4,5,4,3,3,3,1,2,2,1,1,4,4,3},
  {2,3,4,4,4,1,1,1,2,1,3,3,3,0,1,1,2,6,2,5,4,5,3,3,2,3,4,4,4,5,5,3,3,1,6,5},
  {2,3,4,4,4,1,2,2,3,2,3,3,3,1,0,1,2,6,1,5,3,4,2,2,1,2,4,3,4,5,5,3,3,2,6,4},
  {1,2,3,3,3,2,2,2,2,1,2,2,2,1,1,0,1,5,1,4,3,4,3,3,2,2,3,3,3,4,4,2,2,2,5,4},
  {1,1,2,2,2,3,3,2,1,1,1,1,1,2,2,1,0,4,2,3,3,4,3,4,3,2,2,2,2,3,3,1,1,3,4,3},
  {4,3,4,2,3,6,7,6,5,5,5,3,4,6,6,5,4,0,5,1,5,6,5,6,5,4,2,3,5,4,2,5,5,7,2,3},
  {1,2,3,3,4,2,3,3,3,2,3,3,3,2,1,1,2,5,0,4,2,3,2,2,1,1,3,2,4,5,4,3,3,3,5,3},
  {3,2,3,1,2,5,6,5,4,4,4,2,3,5,5,4,3,1,4,0,4,5,4,5,4,3,1,2,4,3,1,4,4,6,1,2},
  {2,3,4,4,5,3,5,4,4,3,4,4,4,4,3,3,3,5,2,4,0,1,1,3,2,1,3,2,5,6,5,4,4,5,5,3},
  {3,4,5,5,6,4,6,5,5,4,5,5,5,5,4,4,4,6,3,5,1,0,2,4,3,2,4,3,6,7,6,5,5,6,6,4},
  {2,3,4,4,5,2,4,4,4,3,4,4,4,3,2,3,3,5,2,4,1,2,0,2,1,1,3,2,5,6,5,4,4,4,5,3},
  {3,4,5,5,6,2,4,4,5,4,5,5,5,3,2,3,4,6,2,5,3,4,2,0,1,2,4,3,6,7,6,5,5,4,6,4},
  {2,3,4,4,5,1,3,3,4,3,4,4,4,2,1,2,3,5,1,4,2,3,1,1,0,1,3,2,5,6,5,4,4,3,5,3},
  {1,2,3,3,4,2,4,3,3,2,3,3,3,3,2,2,2,4,1,3,1,2,1,2,1,0,2,1,4,5,4,3,3,4,4,2},
  {2,1,2,1,2,4,5,4,3,3,3,2,3,4,4,3,2,2,3,1,3,4,3,4,3,2,0,1,4,3,2,3,3,5,2,1},
  {2,1,2,2,3,3,5,4,3,3,3,2,3,4,3,3,2,3,2,2,2,3,2,3,2,1,1,0,4,4,3,3,3,5,3,1},
  {3,3,4,3,2,5,5,4,3,3,2,2,1,4,4,3,2,5,4,4,5,6,5,6,5,4,4,4,0,1,3,1,2,5,5,4},
  {4,3,4,2,1,6,6,5,4,4,3,2,2,5,5,4,3,4,5,3,6,7,6,7,6,5,3,4,1,0,2,2,3,6,4,3},
  {3,2,3,1,1,6,6,5,4,4,4,2,2,5,5,4,3,2,4,1,5,6,5,6,5,4,2,3,3,2,0,3,3,6,2,2},
  {2,2,3,3,2,4,4,3,2,2,1,2,1,3,3,2,1,5,3,4,4,5,4,5,4,3,3,3,1,2,3,0,1,4,5,4},
  {2,2,3,3,2,4,4,3,2,2,2,2,1,3,3,2,1,5,3,4,4,5,4,5,4,3,3,3,2,3,3,1,0,4,5,4},
  {3,4,5,5,5,2,2,2,3,2,4,4,4,1,2,2,3,7,3,6,5,6,4,4,3,4,5,5,5,6,6,4,4,0,7,6},
  {4,3,4,2,3,6,7,6,5,5,5,3,4,6,6,5,4,2,5,1,5,6,5,6,5,4,2,3,5,4,2,5,5,7,0,3},
  {3,2,3,1,2,4,6,5,4,4,4,2,3,5,4,4,3,3,3,2,3,4,3,4,3,2,1,1,4,3,2,4,4,6,3,0}};

uint8_t zip_distance(uint16_t zip1, uint16_t zip2) {
  zip1 = (uint8_t) reduce_zip(zip1);
  zip2 = (uint8_t) reduce_zip(zip2);
  if(zip1 == 255 || zip2 == 255) return 255;
  return zip[zip1][zip2];
}

digraph_t *digraph_init(uint32_t nNumSourceNodes) {
  digraph_t *pDigraph = (digraph_t *)malloc(1 * sizeof(digraph_t));
  pDigraph->nNumSourceNodes = nNumSourceNodes;
  pDigraph->edges = (edges_t **)malloc(nNumSourceNodes * sizeof(edges_t *));
  for(uint32_t i = 0; i < nNumSourceNodes; i++) {
    pDigraph->edges[i] = edges_t_alloc(10, 10);
  }
  return pDigraph;
}

uint32_t *print_digraph(FILE *fout, digraph_t *pDigraph, youths_t *youths, jobs_t *jobs) {
  fprintf(fout, "graph [\n");
  fprintf(fout, "directed 1\n");

  //Also need an inverse mapping for efficient lookup.
  uint32_t nNumNodes = 0;
  for(uint32_t i = 0; i < youths->nLength; i++) {
    youth_t *youth = youths_t_at(youths, i);
    if(youth->in_graph) {
      youth->mapping = nNumNodes++;
      fprintf(fout, "node [ id %u ]\n", youth->mapping);
    }
  }

  uint32_t jobs_not_matched = 0;
  uint32_t total_jobs = nNumNodes;
  for(uint32_t i = 0; i < jobs->nLength; i++) {
    job_t *job = jobs_t_at(jobs, i);
    if(job->in_graph) {
      job->mapping = nNumNodes++;
      fprintf(fout, "node [ id %u ]\n", job->mapping);
    } else {
      if(!job->in_graph) {
        fprintf(stderr, "Job (%u, %s) cannot be matched to any youth\n", job->worksite_id, job->position_name);
        jobs_not_matched++;
      }
    }
  }
  fprintf(stderr, "Total unmatchable jobs = %u\n", jobs_not_matched);
  
  total_jobs = nNumNodes - total_jobs;
  fprintf(stderr, "Total number of jobs available = %u\n", total_jobs);

  uint32_t *inverse_mapping = (uint32_t *)calloc(sizeof(uint32_t), nNumNodes);
  
  for(uint32_t i = 0; i < youths->nLength; i++) {
    youth_t *youth = youths_t_at(youths, i);
    if(youth->in_graph) {
      inverse_mapping[youth->mapping] = youth->csv_row_id;
      for(uint32_t j = 0; j < pDigraph->edges[youth->csv_row_id]->nLength; j++) {
        edge_t *edge = edges_t_at(pDigraph->edges[youth->csv_row_id], j);
        fprintf(fout, "edge [ source %u\ntarget %u\n label \"%u\" ]\n",
                youth->mapping, jobs->pList[edge->sink]->mapping, edge->weight);
        inverse_mapping[jobs->pList[edge->sink]->mapping] = edge->sink;
      }
    }
  }
  fprintf(fout, "]\n");

  return inverse_mapping;
}

void add_edge(digraph_t *pDigraph, youth_t *youth, job_t *job, uint32_t mapping) {
  uint32_t i, j;

  uint8_t print_warning = 0;
  
  //Hard constraints

  if(youth->age < job->minimum_age) {
    if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because of minimum age\n", youth->youth_id, job->worksite_id);
    return;
  }
  if(youth->age > job->maximum_age) {
    if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because of maximum age\n", youth->youth_id, job->worksite_id);
    return;
  }

  if(youth->zip != job->zip) {
    if(youth->zip_flexible == 0) {
      if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because not in zip code and not zip flexible\n", youth->youth_id, job->worksite_id);
      return;
    } else {
      //If zip codes do not match, part of city for worksite matches
      //part of city youth is willing to travel to (only if youth
      //listed "Yes" to willing to travel outside zip code)
      
      uint8_t found_cityside_match = 0;
      for(i = 0; i < youth->num_sides; i++) {
	if(strcmp(youth->sides_of_city[i], job->side_of_city) == 0) {
	  found_cityside_match = 1;
	  break;
	}
      }
      if(!found_cityside_match) {
	if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because neither zip code (%u, %u) nor city sides match\n", youth->youth_id, job->worksite_id, youth->zip, job->zip);
	return;
      }
    }
  }

  if(job->num_school_requests > 0) {
    if(youth->school_status[0] == 'I') {
      uint8_t school_number_matched = 0;
      for(i = 0; i < job->num_school_requests; i++) {
	if(job->school_requests[i] == youth->school_number) {
	  school_number_matched = 1;
	  break;
	}
      }
      if(school_number_matched == 0) {
	if(print_warning)
	  fprintf(stderr, "Youth %u cannot have job %u because they are not attenting one of the requested schools\n", youth->youth_id, job->worksite_id);
	return;
      }
    } else {
      if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because they are not attenting school\n", youth->youth_id, job->worksite_id);
      return;
    }
  }

  if(job->num_grade_requests > 0) {
    if(youth->school_status[0] == 'I' || youth->school_status[23] != 'D') {
      uint8_t grade_request_match = 0;
      for(i = 0; i < job->num_grade_requests; i++) {
	if(strcmp(job->grade_requests[i], youth->highest_grade_completed) == 0) {
	  grade_request_match = 1;
	  break;
	}
      }
      if(grade_request_match == 0) {
	if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because their grade does not match any of the job's required grades\n", youth->youth_id, job->worksite_id);
	return;
      }
    } else {
      if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because they are not attenting school and did not graduate\n", youth->youth_id, job->worksite_id);
      return;
    }

  }

  if(!youth->outside && job->outside) {
    if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because they don't want to work outside\n", youth->youth_id, job->worksite_id);
    return;
  }
  
  for(i = 0; i < 7; i++) {
    if(youth->job_choices[i] == 0) {
      if(print_warning) fprintf(stderr, "Youth %u cannot have any job because their job choices section was incomplete\n", youth->youth_id);
      return;
    }
  }

  //Youth has skills *required* by the job
  char *must_match[] = {"SWIMMING", "PLAYS INSTRUMENT", "DANCING", "MICROSOFT"};
  for(i = 0; i < 4; i++) {
    uint8_t in_list = 0;
    for(j = 0; j < job->num_skills; j++) {
      if(strcmp(must_match[i], job->skills[j]) == 0) {
        in_list = 1; break;
      }
    }
    if(in_list) {
      in_list = 0;
      for(j = 0; j < youth->num_skills; j++) {
        if(strcmp(must_match[i], youth->skills[j]) == 0) {
          in_list = 1; break;
        }
      }
      if(in_list == 0) {
        if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because job requires %s and youth does not have that skill\n", youth->youth_id, job->worksite_id, must_match[i]);
        return;
      }
    }
  }

  //Count the number of the Youth's positive job choices and determine if any agree with the job's
  uint32_t num_job_choices = 0;
  uint8_t some_job_choice_agrees = 0;
  for(i = 0; i < 7; i++) {
    if(youth->job_choices[i] == 2) {
      num_job_choices++;
      if(job->job_choices[i] == 2) {
	some_job_choice_agrees = 1;
      }
    }
  }

  /* No longer an essential constraint
  if(!some_job_choice_agrees) {
    if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because the youth's job choices do not align with the job\n", youth->youth_id, job->worksite_id);
    return;
  }
  */
  
  uint8_t some_career_interest_matches = 0;
  //Some Youth career interest matches job's
  for(i = 0; i < job->num_interests; i++) {
    if((strcmp(youth->career_interest1, job->career_interests[i]) == 0) || (strcmp(youth->career_interest2, job->career_interests[i]) == 0)) {
      some_career_interest_matches = 1;
      break;
    }
  }

  if(!some_career_interest_matches) {
    if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because neither of the youth's career interests match those of the job\n", youth->youth_id, job->worksite_id);
    return;
  }

  edge_t *edge = (edge_t *)malloc(1 * sizeof(edge_t));
  edge->sink = mapping;

  youth->in_graph = 1;
  job->in_graph = 1;

  int32_t weight = 1;
  
  if(pDigraph->use_soft_constraints) {
    //Soft constraints
    
    int32_t num_agrees = 1;

    //Youth zip is close to job zip
    uint8_t youth_zip_distance = zip_distance(youth->zip, job->zip);
    if(youth_zip_distance == 255) {
      if(print_warning) fprintf(stderr, "Youth %u cannot have job %u because one of the two zip codes is not in the zip matrix\n", youth->youth_id, job->worksite_id);
      return;
    }

    if(youth_zip_distance == 1) {
      num_agrees+=2;
    } else if(youth_zip_distance == 2) {
      num_agrees+=1;
    } else if(youth_zip_distance == 3) {
      num_agrees-=1;
    } else if(youth_zip_distance == 4) {
      num_agrees-=2;
    } else if(youth_zip_distance == 5) {
      num_agrees-=3;
    } else if(youth_zip_distance == 6) {
      num_agrees-=4;
    } else if(youth_zip_distance == 7) {
      num_agrees-=5;
    }

    if(job->second_language[0] != 0) {
      if(strcmp(job->second_language, youth->second_language) == 0) {
	if(job->second_language_proficiency < youth->second_language_proficiency) {
	  num_agrees += 2;
	} else if(job->second_language_proficiency == youth->second_language_proficiency) {
	  num_agrees += 3;
	} else if(youth->second_language_proficiency > 0) {
	  num_agrees += 1;
	}
      }
    }

    //Youth's outside preference matches job's
    num_agrees += youth->outside == job->outside;

    //Youth's dress code preference matches job's
    num_agrees += youth->dress_code == job->dress_code;

    //Youth's computer preference matches job's
    num_agrees += youth->computers == job->computers;

    if(some_job_choice_agrees) {
      if(num_job_choices == 7) {
	//no extra weight
      } else if(num_job_choices > 4) {
	num_agrees += 1; //5 or 6 choices selected
      } else if(num_job_choices > 1) {
	num_agrees += 2; //2,3, or 4 choices selected
      } else { //1 choice selected, really strongly match
	num_agrees += 3;
      }
    }

    char *desired_interests[] = {"CLERICAL OFFICE WORK", "RECREATION AND SPORTS", "CAMP COUNSELOR", "COMPUTER INFORMATION TECH", "CULINARY ARTS/FOOD SERVICE", "CUSTODIAL", "ENVIRONMENTAL/GREEN", "MUSICAL ARTS", "NURSING", "BUSINESS/FINANCE"};

    //Youth's first career interest matches job's
    for(i = 0; i < job->num_interests; i++) {
      if(strcmp(youth->career_interest1, job->career_interests[i]) == 0) {
        num_agrees+=2;
        //Is this a good way to make career interest 1 more
        //important than 2?

	for(j = 0; j < 10; j++) {
	  if(strcmp(youth->career_interest1, desired_interests[j]) == 0) {
	    num_agrees+=1;
	    break;
	  }
	}
	
        break;
      }
    }

    //Youth's second career interest matches job's
    for(i = 0; i < job->num_interests; i++) {
      if(strcmp(youth->career_interest2, job->career_interests[i]) == 0) {
        num_agrees+=1;
        
	for(j = 0; j < 10; j++) {
	  if(strcmp(youth->career_interest2, desired_interests[j]) == 0) {
	    num_agrees+=1;
	    break;
	  }
	}

	break;
      }
    }

    //Youth has interests desired by job
    char *desired_match[] = {"VISUAL ARTS", "OFFICE EQUIPMENT", "POETRY"};
    for(i = 0; i < 3; i++) {
      uint8_t in_list = 0;
      for(j = 0; j < job->num_skills; j++) {
        if(strcmp(desired_match[i], job->skills[j]) == 0) {
          in_list = 1; break;
        }
      }
      if(in_list) {
        for(j = 0; j < youth->num_skills; j++) {
          if(strcmp(desired_match[i], youth->skills[j]) == 0) {
	    if(j == 2) { // OFFICE EQUIPMENT
	      num_agrees+=2;
	    } else {
	      num_agrees+=1;
	    }
	    break;
          }
        }
      }
    }
    
    double exponent = (double) num_agrees;
    exponent += (2.0 - (double) youth->priority)*18.0;
    if(exponent < 0.0) exponent = 0;
    if(exponent > 60.0) exponent = 60.0;
    double weight_d = pow(1.3, exponent) - 1.3;

    weight = (int32_t)weight_d;
  }

  edge->weight = weight;

  if(weight > youth->best_weight) {
    youth->best_weight = weight;
  }
  
  edges_t_push(pDigraph->edges[youth->csv_row_id], edge);
}

digraph_t *create_digraph(youths_t *youths, jobs_t *jobs, uint8_t use_soft_constraints) {
  digraph_t *pDigraph = digraph_init(youths->nLength+1);

  pDigraph->use_soft_constraints = use_soft_constraints;

  uint32_t youth_not_matched = 0;
  
  for(uint32_t i = 0; i < youths->nLength; i++) {
    youth_t *youth = youths_t_at(youths, i);
    for(uint32_t j = 0; j < jobs->nLength; j++) {
      job_t *job = jobs_t_at(jobs, j);
      add_edge(pDigraph, youth, job, j);
    }

    if(!youth->in_graph) {
      fprintf(stderr, "Youth %u cannot be matched to any job\n", youth->youth_id);
      youth_not_matched++;
    }
  }

  fprintf(stderr, "Total unmatchable youth = %u\n", youth_not_matched);
  fprintf(stderr, "Total number of youth available = %u\n", youths->nLength - youth_not_matched);
  
  return pDigraph;
}

void digraph_free(digraph_t *pDigraph) {
  for(uint32_t i = 0; i < pDigraph->nNumSourceNodes; i++) {
    for(uint32_t j = 0; j < pDigraph->edges[i]->nLength; j++) {
      free(pDigraph->edges[i]->pList[j]);
    }
    edges_t_free(pDigraph->edges[i]);
    free(pDigraph->edges[i]);
  }
  free(pDigraph->edges);
  free(pDigraph);
}
