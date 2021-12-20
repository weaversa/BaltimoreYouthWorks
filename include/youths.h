#ifndef YOUTH_H
#define YOUTH_H

#include "youthworks.h"

typedef struct youth_t {
  uint32_t csv_row_id;
  uint8_t in_graph;
  uint32_t mapping;
  int32_t best_weight;
  uint32_t youth_id;
  uint8_t age;
  uint16_t zip;
  uint8_t zip_flexible; //Willing to travel outside zip code?
  uint8_t num_sides;
  char **sides_of_city;
  uint8_t outside;
  uint8_t dress_code;
  uint8_t computers;
  char *career_interest1;
  char *career_interest2;
  uint8_t num_skills;
  char **skills;
  uint8_t job_choices[7]; //Job Choice A - G
  char *second_language;
  uint8_t second_language_proficiency;
  uint32_t school_number;
  char *school_status;
  char *highest_grade_completed;
  uint8_t priority;
} youth_t; //All subject to change

create_list_headers(youths_t, youth_t *)

youths_t *create_youth_list(csv_data *pYouthCSV);
void free_youth_list(youths_t *youths);

void strrep(char *string, char a, char b);

#endif
