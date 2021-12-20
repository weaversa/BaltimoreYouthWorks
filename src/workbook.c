#include "youthworks.h"
#include <wordexp.h>

uint32_t hibit(uint32_t n) {
  uint32_t r = 0;
  while (n >>= 1) {
    r++;
  }
  return r;
}

#define MATCH(a,b) (a == b ? green : NULL)
#define SMATCH(a,b) (strcmp(a,b)==0 ? green : NULL)
#define YES(a) (a ? "YES" : "NO")

void create_workbook(matched_pairs_t *pairs, youths_t *youths, jobs_t *jobs) {
  uint32_t_list *choices_list = uint32_t_list_alloc(10, 10);
  for(uint32_t i = 0; i < 10; i++) {
    uint32_t_list_push(choices_list, 0);
  }

  wordexp_t exp_result;
  wordexp("/output/YouthworksMatching.xlsx", &exp_result, 0);
  lxw_workbook  *workbook  = workbook_new(exp_result.we_wordv[0]);
  wordfree(&exp_result);

  //Create the format for matched elements
  lxw_format *green = workbook_add_format(workbook);
  // Set some of the format properties.
  format_set_bg_color(green, 0x9bff9b);
  
  lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
  worksheet_write_string(worksheet, 0, 0, "Youth ID", NULL);
  worksheet_write_string(worksheet, 0, 1, "Worksite ID", NULL);
  worksheet_write_string(worksheet, 0, 2, "Position Name", NULL);
  worksheet_write_string(worksheet, 0, 3, "Choice", NULL);
  worksheet_write_string(worksheet, 0, 4, "Age at Registration", NULL);
  worksheet_write_string(worksheet, 0, 5, "Zip Code", NULL);
  worksheet_write_string(worksheet, 0, 6, "Travel to Another Zipcode", NULL);
  worksheet_write_string(worksheet, 0, 7, "Part of City", NULL);
  worksheet_write_string(worksheet, 0, 8, "Interested in Working Outside", NULL);
  worksheet_write_string(worksheet, 0, 9, "Interested in Working With Dress Code", NULL);
  worksheet_write_string(worksheet, 0, 10, "Interested in Working With Computers", NULL);
  worksheet_write_string(worksheet, 0, 11, "Career Interest Category 1", NULL);
  worksheet_write_string(worksheet, 0, 12, "Career Interest Category 2", NULL);
  worksheet_write_string(worksheet, 0, 13, "List of Matched Skills", NULL);
  worksheet_write_string(worksheet, 0, 14, "Matching Job Choice", NULL);
  worksheet_write_string(worksheet, 0, 15, "Second Language", NULL);
  worksheet_write_string(worksheet, 0, 16, "School Number", NULL);
  worksheet_write_string(worksheet, 0, 17, "School Status", NULL);
  worksheet_write_string(worksheet, 0, 18, "Highest Grade Completed", NULL);
  worksheet_write_string(worksheet, 0, 19, "Priority", NULL);
  worksheet_write_string(worksheet, 0, 20, "Weight", NULL);
  
  uint32_t nRows = 1;
  for(uint32_t i = 0; i < pairs->nLength; i++) {
    matched_pair_t *pair = matched_pairs_t_at(pairs, i);
    youth_t *youth = youths_t_at(youths, pair->youth_id);
    job_t *job = jobs_t_at(jobs, pair->job_id);
    worksheet_write_number(worksheet, nRows, 0, youth->youth_id, NULL);

    int32_t choice = 1 + hibit(youth->best_weight+1) - hibit(pair->weight+1);
    choices_list->pList[choice]++;

    worksheet_write_number(worksheet, nRows, 1, job->worksite_id, NULL);
    worksheet_write_string(worksheet, nRows, 2, job->position_name, NULL);
    
    int32_t k=(choice+9)%10;
    char *end[4] = {"st", "nd", "rd", "th"};
    char ordinal[10];
    snprintf(ordinal, 10, "%d%s",choice,k<3?end[k]:end[3]);
    worksheet_write_string(worksheet, nRows, 3, ordinal, NULL);
    worksheet_write_number(worksheet, nRows, 4, youth->age, green);
    worksheet_write_number(worksheet, nRows, 5, youth->zip,
                           MATCH(youth->zip,job->zip));
    worksheet_write_string(worksheet, nRows, 6, YES(youth->zip_flexible), NULL);
    worksheet_write_string(worksheet, nRows, 7, job->side_of_city, green);
    worksheet_write_string(worksheet, nRows, 8, YES(youth->outside),
                           MATCH(youth->outside, job->outside));
    worksheet_write_string(worksheet, nRows, 9, YES(youth->dress_code),
                             MATCH(youth->dress_code, job->dress_code));
    worksheet_write_string(worksheet, nRows, 10, YES(youth->computers),
                           MATCH(youth->computers, job->computers));
    
    uint8_t career_match = 0;
    for(uint32_t j = 0; j < job->num_interests; j++) {
      if(strcmp(youth->career_interest1, job->career_interests[j]) == 0) {
        career_match = 1;
        break;
      }
    }
    worksheet_write_string(worksheet, nRows, 11, youth->career_interest1,
                           career_match ? green : NULL);
    
    career_match = 0;
    for(uint32_t j = 0; j < job->num_interests; j++) {
      if(strcmp(youth->career_interest2, job->career_interests[j]) == 0) {
        career_match = 1;
        break;
      }
    }
    worksheet_write_string(worksheet, nRows, 12, youth->career_interest2,
                           career_match ? green : NULL);
    
    char skills[2048]; skills[0] = 0;
    
    char *must_match[] = {"SWIMMING", "CADD", "PLAYS INSTRUMENT", "DANCING", "MICROSOFT"};
    for(uint32_t k = 0; k < 5; k++) {
      uint8_t in_list = 0;
      for(uint32_t j = 0; j < job->num_skills; j++) {
        if(strcmp(must_match[k], job->skills[j]) == 0) {
          in_list = 1; break;
        }
      }
      if(in_list) {
        for(uint32_t j = 0; j < youth->num_skills; j++) {
          if(strcmp(must_match[k], youth->skills[j]) == 0) {
            if(skills[0] != 0) strcat(skills, ",");
            strcat(skills, youth->skills[j]);
            break;
          }
        }
      }
    }
    
    uint8_t found_desired = 0;
    char *desired_match[] = {"VISUAL ARTS", "OFFICE EQUIPMENT", "POETRY"};
    for(uint32_t k = 0; k < 3; k++) {
      uint8_t in_list = 0;
      for(uint32_t j = 0; j < job->num_skills; j++) {
        if(strcmp(desired_match[k], job->skills[j]) == 0) {
          in_list = 1; break;
        }
      }
      if(in_list) {
        for(uint32_t j = 0; j < youth->num_skills; j++) {
          if(strcmp(desired_match[k], youth->skills[j]) == 0) {
            if(skills[0] != 0) strcat(skills, ",");
            strcat(skills, youth->skills[j]);
            found_desired = 1;
            in_list = 1; break;
          }
        }
      }
    }
    
    worksheet_write_string(worksheet, nRows, 13, skills, found_desired ? green : NULL);
    
    for(uint32_t j = 0; j < 7; j++) {
      if(youth->job_choices[j] == 2 && job->job_choices[j] == 2) {
        char choice[2] = {'A', 0};
        choice[0] += j;
        worksheet_write_string(worksheet, nRows, 14, choice, green);
        break;
      }
    }
    
    worksheet_write_string(worksheet, nRows, 15, youth->second_language, strcmp(youth->second_language, job->second_language) == 0 ? green : NULL);

    uint8_t school_number_matched = job->num_school_requests == 0;
    for(uint32_t j = 0; j < job->num_school_requests; j++) {
      if(job->school_requests[j] == youth->school_number) {
	school_number_matched = 1;
	break;
      }
    }
    
    worksheet_write_number(worksheet, nRows, 16, youth->school_number, school_number_matched ? green : NULL);
    
    uint8_t school_status_matched = job->num_school_requests == 0;
    if(job->num_school_requests > 0) {
      if(youth->school_status[0] == 'I') {
	school_status_matched = 1;
      }
    }

    worksheet_write_string(worksheet, nRows, 17, youth->school_status, school_status_matched == 1 ? green : NULL);

    uint8_t grade_request_match = job->num_grade_requests == 0;
    for(uint32_t j = 0; j < job->num_grade_requests; j++) {
      if(strcmp(job->grade_requests[j], youth->highest_grade_completed) == 0) {
	grade_request_match = 1;
	break;
      }
    }
    
    worksheet_write_string(worksheet, nRows, 18, youth->highest_grade_completed, grade_request_match == 1 ? green : NULL);

    if(youth->priority == 0) {
      worksheet_write_string(worksheet, nRows, 19, "MANDATORY", NULL);
    } else if(youth->priority == 1) {
      worksheet_write_string(worksheet, nRows, 19, "PREFERRED", NULL);
    } else {
      worksheet_write_string(worksheet, nRows, 19, "NONE", NULL);
    }

    worksheet_write_number(worksheet, nRows, 20, pair->weight, NULL);
    
    nRows++;
    
    
    //fprintf(stdout, "%u,%u,%d\n", pairs->youth_id, pairs->job_id, pairs->weight);
  }
  //fprintf(stdout, "\n");

  //Print some statistics
  fprintf(stderr, "Matched %u youth to jobs\n", pairs->nLength);

  uint32_t nNumYouthSeen = 0;
  for(uint32_t i = 1; i < choices_list->nLength; i++) {
    uint32_t nNumYouth = uint32_t_list_at(choices_list, i);
    
    int32_t k=(i+9)%10;
    char *end[4] = {"st", "nd", "rd", "th"};
    char ordinal[10];
    snprintf(ordinal, 10, "%d%s",i,k<3?end[k]:end[3]);

    float percentage = 100.0 * ((float)nNumYouth) / ((float)pairs->nLength);
    
    fprintf(stderr, "%u Youth (%1.0f%%) got their %s choice\n", nNumYouth, percentage, ordinal);

    nNumYouthSeen += nNumYouth;
    if(nNumYouthSeen == pairs->nLength) break;
  }
  
  uint32_t_list_free(choices_list);
  free(choices_list);
  
  uint8_t xls_ret = workbook_close(workbook);
}
