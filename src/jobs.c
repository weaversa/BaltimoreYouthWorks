#include "youthworks.h"

create_list_type(jobs_t, job_t *)

job_t *csv_row_to_job(csv_data *pJobsCSV, uint32_t nRow, uint32_t job_id) {
  uint32_t i;
  
  uint8_t_plist *row = &pJobsCSV->pRow[nRow];

  job_t *job = (job_t *)calloc(1, sizeof(job_t));
  job->csv_row_id = nRow-1;

  job->in_graph = 0;
  
  //Worksite ID
  job->worksite_id = strtol((char *)uint8_t_plist_at(row, 0), NULL, 10);

  //Position Name
  char *position_name = (char *)uint8_t_plist_at(row, 1);
  job->position_name = malloc((strlen(position_name)+1) * sizeof(char));
  strcpy(job->position_name, position_name);

  //Minimum and Maximum Age
  job->minimum_age = strtol((char *)uint8_t_plist_at(row, 5), NULL, 10);
  job->maximum_age = strtol((char *)uint8_t_plist_at(row, 6), NULL, 10);
  
  //Zip
  job->zip = strtol((char *)uint8_t_plist_at(row, 8), NULL, 10);

  if(job->zip == 0) {
    fprintf(stderr, "Job (%u, %s) is missing a zip code\n", job->worksite_id, job->position_name);
  }

  //Side of City
  char *side = (char *)uint8_t_plist_at(row, 9);
  job->side_of_city = malloc((strlen(side)+1) * sizeof(char));
  strcpy(job->side_of_city, side);

  //Working Outside
  job->outside = uint8_t_plist_at(row, 10)[0] == 'Y';

  //Dress Code
  job->dress_code = uint8_t_plist_at(row, 11)[0] == 'Y';

  //With Computers
  job->computers = uint8_t_plist_at(row, 12)[0] == 'Y';

  //Career Interests
  //char **career_interests;
  char *career_interests = stradd((char *)uint8_t_plist_at(row, 13), "\n");
  csv_data *pCareerInterestsCSV = csv_read_buffer(career_interests, strlen(career_interests)+1);
  free(career_interests);

  job->num_interests = pCareerInterestsCSV->pRow->nLength;
  job->career_interests = (char **)malloc(job->num_interests * sizeof(char *));

  for(i = 0; i < job->num_interests; i++) {
    char *career_interest = (char *)uint8_t_plist_at(&pCareerInterestsCSV->pRow[0], i);
    job->career_interests[i] = malloc((strlen(career_interest)+1) * sizeof(char));
    strcpy(job->career_interests[i], career_interest);
  }

  csv_data_free(pCareerInterestsCSV);
  
  //Skills
  char *skills = stradd((char *)uint8_t_plist_at(row, 14), "\n");
  //Clean up parenthesis
  strrep(skills, '(', ' ');
  strrep(skills, ')', ' ');
  
  csv_data *pSkillsCSV = csv_read_buffer(skills, strlen(skills)+1);
  free(skills);

  job->num_skills = pSkillsCSV->pRow->nLength;
  job->skills = (char **)malloc(job->num_skills * sizeof(char *));

  for(i = 0; i < job->num_skills; i++) {
    char *skill = (char *)uint8_t_plist_at(&pSkillsCSV->pRow[0], i);
    job->skills[i] = malloc((strlen(skill)+1) * sizeof(char));
    strcpy(job->skills[i], skill);
    //fprintf(stderr, "|%s|", job->skills[i]);
  }

  csv_data_free(pSkillsCSV);
  
  //Job Choice A-H
  for(i = 0; i < 7; i++) {
    uint8_t *job_choice = uint8_t_plist_at(row, i+15);
    if(job_choice[0] == 0) {          //Not Answered
      job->job_choices[i] = 0;
    } else if(job_choice[0] == 'N') { //NOT APPLICABLE
      job->job_choices[i] = 1;
    } else {                          //MOST CLOSELY MATCHES
      job->job_choices[i] = 2;
    }
  }

  //Second Language
  char *second_language = (char *)uint8_t_plist_at(row, 22);
  job->second_language = malloc((strlen(second_language)+1) * sizeof(char));
  strcpy(job->second_language, second_language);

  //Second Language Proficiency
  char *second_language_proficiency = (char *)uint8_t_plist_at(row, 23);
  job->second_language_proficiency = second_language_proficiency[0] - '0';

  //School Requests
  if(((char *)uint8_t_plist_at(row, 24))[0] == 'N') {
    job->num_school_requests = 0;
  } else {
    strrep((char *)uint8_t_plist_at(row, 24), '\n', ',');
    char *school_requests = stradd((char *)uint8_t_plist_at(row, 24), "\n");
    
    csv_data *pSchoolRequestsCSV = csv_read_buffer(school_requests, strlen(school_requests)+1);
    free(school_requests);
    
    job->num_school_requests = pSchoolRequestsCSV->pRow->nLength;
    job->school_requests = (uint32_t *)malloc(job->num_school_requests * sizeof(uint32_t));
    
    for(i = 0; i < job->num_school_requests; i++) {
      char *request = (char *)uint8_t_plist_at(&pSchoolRequestsCSV->pRow[0], i);
      job->school_requests[i] = strtol(request, NULL, 10);
    }
    
    csv_data_free(pSchoolRequestsCSV);
  }
    
  //Grade Requests
  if(((char *)uint8_t_plist_at(row, 25))[0] == 'N') {
    job->num_grade_requests = 0;
  } else {
    char *grade_requests = stradd((char *)uint8_t_plist_at(row, 25), "\n");
    csv_data *pGradeRequestsCSV = csv_read_buffer(grade_requests, strlen(grade_requests)+1);
    free(grade_requests);
    
    job->num_grade_requests = pGradeRequestsCSV->pRow->nLength;
    job->grade_requests = (char **)malloc(job->num_grade_requests * sizeof(char *));
    
    for(i = 0; i < job->num_grade_requests; i++) {
      char *request = (char *)uint8_t_plist_at(&pGradeRequestsCSV->pRow[0], i);
      job->grade_requests[i] = malloc((strlen(request)+1) * sizeof(char));
      strcpy(job->grade_requests[i], request);
    }
    
    csv_data_free(pGradeRequestsCSV);
  }
    
  return job;
}

jobs_t *create_job_list(csv_data *pJobsCSV) {
  jobs_t *jobs = jobs_t_alloc(10, 10);

  for(uint32_t i = 1; i < pJobsCSV->nRows; i++) {
    //Youth Requested
    uint8_t_plist *row = &pJobsCSV->pRow[i];

    uint32_t num_positions_approved = strtol((char *)uint8_t_plist_at(row, 2), NULL, 10);
    uint32_t num_positions_filled = strtol((char *)uint8_t_plist_at(row, 3), NULL, 10);
    uint32_t yw_staff_match_number = strtol((char *)uint8_t_plist_at(row, 7), NULL, 10);
    
    //On the advice of Jon Smeton, here we consider the number of open positions to be the minimum of either the number of approved positions minus the number of positions filled or the yw_staff_match_number.
    uint32_t num_positions = num_positions_approved - num_positions_filled;

    //Check for underflow
    if(num_positions_filled > num_positions_approved)
      num_positions = 0;
    uint32_t num_jobs = num_positions < yw_staff_match_number ? num_positions : yw_staff_match_number;

    uint8_t print_warning = 1;
    for(uint32_t j = 0; j < num_jobs; j++) {
      job_t *job = csv_row_to_job(pJobsCSV, i, j);
      if(job->minimum_age > job->maximum_age) {
        if(print_warning) fprintf(stderr, "Warning!!! Worksite %u has minimum age greater than maximum age...removing worksite\n", job->worksite_id);
        job_t_free(job);
        print_warning = 0;
        continue;
      }
      uint8_t job_bad = 0;
      for(uint32_t k = 0; k < 7; k++) {
        if(job->job_choices[k] == 0) {
          if(print_warning) fprintf(stderr, "Worksite %u is being removed because the job choices section was incomplete\n", job->worksite_id);
          job_t_free(job);
          print_warning = 0;
          job_bad = 1; break;
        }
      }
      if(job_bad) continue;
      
      jobs_t_push(jobs, job);
    }
  }

  return jobs;
}

void job_t_free(job_t *job) {
  uint32_t i;

  free(job->position_name);
  free(job->side_of_city);
  for(i = 0; i < job->num_interests; i++)
    free(job->career_interests[i]);
  free(job->career_interests);
  for(i = 0; i < job->num_skills; i++)
    free(job->skills[i]);
  free(job->skills);
  free(job->second_language);
  free(job->school_requests);
  for(i = 0; i < job->num_grade_requests; i++)
    free(job->grade_requests[i]);
  free(job->grade_requests);
  free(job);
}

void free_job_list(jobs_t *jobs) {
  for(uint32_t i = 0; i < jobs->nLength; i++) {
    job_t_free(jobs->pList[i]);
  }
  jobs_t_free(jobs);
  free(jobs);
}
