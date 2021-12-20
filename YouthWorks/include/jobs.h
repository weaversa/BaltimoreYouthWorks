#ifndef JOBS_H
#define JOBS_H

#include "youthworks.h"

typedef struct job_t {
  uint32_t csv_row_id; //Maybe unnecessary
  uint8_t in_graph;
  uint32_t mapping;

  uint32_t worksite_id;
  char *position_name;
  uint8_t minimum_age;
  uint8_t maximum_age;
  uint16_t zip;
  char *side_of_city;
  uint8_t outside;
  uint8_t dress_code;
  uint8_t computers;
  uint8_t num_interests;
  char **career_interests;
  uint8_t num_skills;
  char **skills;
  uint8_t job_choices[7];
  char *second_language;
  uint8_t second_language_proficiency;
  uint8_t num_school_requests;
  uint32_t *school_requests;
  uint8_t num_grade_requests;
  char **grade_requests;
} job_t; //All subject to change

create_list_headers(jobs_t, job_t *)

jobs_t *create_job_list(csv_data *pJobsCSV);

void job_t_free(job_t *job);
void free_job_list(jobs_t *jobs);

#endif
