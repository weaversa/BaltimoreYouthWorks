#include "youthworks.h"

create_list_type(youths_t, youth_t *)

void strrep(char *string, char a, char b) {
  size_t length = strlen(string);
  for(uint32_t i = 0; i < length; i++) {
    if(string[i] == a) string[i] = b;
  }
}

void strlshift(char *string) {
  size_t length = strlen(string);
  for(uint32_t i = 1; i < length; i++) {
    string[i-1] = string[i];
  }
  string[length-1] = 0;
}

youth_t *csv_row_to_youth(csv_data *pYouthCSV, uint32_t nRow) {
  uint32_t i;
  
  uint8_t_plist *row = &pYouthCSV->pRow[nRow];

  youth_t *youth = (youth_t *)calloc(1, sizeof(youth_t));
  youth->csv_row_id = nRow-1;

  youth->in_graph = 0;

  youth->best_weight = 0;
  
  //Youth ID
  youth->youth_id = strtol((char *)uint8_t_plist_at(row, 0), NULL, 10);

  //Age
  youth->age = strtol((char *)uint8_t_plist_at(row, 1), NULL, 10);

  //Zip
  youth->zip = strtol((char *)uint8_t_plist_at(row, 2), NULL, 10);

  //Willing to Travel Outside Zip Code
  youth->zip_flexible = uint8_t_plist_at(row, 3)[0] == 'Y';

  //Sides of City
  char *sides_of_city = stradd((char *)uint8_t_plist_at(row, 4), "\n");
  csv_data *pCitySideCSV = csv_read_buffer(sides_of_city, strlen(sides_of_city)+1);
  free(sides_of_city);

  youth->num_sides = pCitySideCSV->pRow->nLength;
  youth->sides_of_city = (char **)malloc(youth->num_sides * sizeof(char *));
  
  for(i = 0; i < youth->num_sides; i++) {
    char *side = (char *)uint8_t_plist_at(&pCitySideCSV->pRow[0], i);
    youth->sides_of_city[i] = malloc((strlen(side)+1) * sizeof(char));
    strcpy(youth->sides_of_city[i], side);
  }
  
  csv_data_free(pCitySideCSV);
  
  //Working Outside
  youth->outside = uint8_t_plist_at(row, 5)[0] == 'Y';

  //Dress Code  
  youth->dress_code = uint8_t_plist_at(row, 6)[0] == 'Y';

  //With Computers
  youth->computers = uint8_t_plist_at(row, 7)[0] == 'Y';

  //Career Interest 1
  char *career_interest = (char *)uint8_t_plist_at(row, 8);
  youth->career_interest1 = malloc((strlen(career_interest)+1) * sizeof(char));
  strcpy(youth->career_interest1, career_interest);

  //Career Interest 2
  career_interest = (char *)uint8_t_plist_at(row, 9);
  youth->career_interest2 = malloc((strlen(career_interest)+1) * sizeof(char));
  strcpy(youth->career_interest2, career_interest);
  
  //Skills
  char *skills = stradd((char *)uint8_t_plist_at(row, 10), "\n");
  //Clean up leading and delimiting semicolons and parenthesis
  strlshift(skills);
  strrep(skills, ';', ',');
  strrep(skills, '(', ' ');
  strrep(skills, ')', ' ');
  
  csv_data *pSkillsCSV = csv_read_buffer(skills, strlen(skills)+1);
  free(skills);

  youth->num_skills = pSkillsCSV->pRow->nLength;
  youth->skills = (char **)malloc(youth->num_skills * sizeof(char *));

  for(i = 0; i < youth->num_skills; i++) {
    char *skill = (char *)uint8_t_plist_at(&pSkillsCSV->pRow[0], i);
    youth->skills[i] = malloc((strlen(skill)+1) * sizeof(char));
    strcpy(youth->skills[i], skill);
    if(strcmp(youth->skills[i], "MICROSOFT WORD") == 0) {
      //Change "MICROSOFT WORD" to "MICROSOFT"
      youth->skills[i][9] = 0;
    }
    //fprintf(stderr, "|%s|", youth->skills[i]);
  }

  csv_data_free(pSkillsCSV);

  //Job Choice A-H
  for(i = 0; i < 7; i++) {
    uint8_t *job_choice = uint8_t_plist_at(row, i+11);
    if(job_choice[0] == 0) {          //Not Answered
      youth->job_choices[i] = 0;
    } else if(job_choice[0] == 'N') { //NOT INTERESTED
      youth->job_choices[i] = 1;
    } else {                          //WORK WITHOUT ACCOMODATION or WORK WITH ACCOMODATION
      youth->job_choices[i] = 2;
    }
  }

  //Second Language
  char *second_language = (char *)uint8_t_plist_at(row, 18);
  youth->second_language = malloc((strlen(second_language)+1) * sizeof(char));
  strcpy(youth->second_language, second_language);

  //Second Language Proficiency
  char *second_language_proficiency = (char *)uint8_t_plist_at(row, 19);
  youth->second_language_proficiency = second_language_proficiency[0] - '0';

  //School Number
  youth->school_number = strtol((char *)uint8_t_plist_at(row, 20), NULL, 10);

  //School Status
  char *school_status = (char *)uint8_t_plist_at(row, 21);
  youth->school_status = malloc((strlen(school_status)+1) * sizeof(char));
  strcpy(youth->school_status, school_status);

  //Highest Grade Completed
  char *highest_grade_completed = (char *)uint8_t_plist_at(row, 22);
  youth->highest_grade_completed = malloc((strlen(highest_grade_completed)+1) * sizeof(char));
  strcpy(youth->highest_grade_completed, highest_grade_completed);

  char priority = ((char *)uint8_t_plist_at(row, 23))[0];
  if(priority == 'M') youth->priority = 0;
  else if(priority == 'P') youth->priority = 1;
  else youth->priority = 2;

  return youth;
}

youths_t *create_youth_list(csv_data *pYouthCSV) {
  youths_t *youths = youths_t_alloc(10, 10);
  
  for(uint32_t i = 1; i < pYouthCSV->nRows; i++) {
    youth_t *youth = csv_row_to_youth(pYouthCSV, i);
    youths_t_push(youths, youth);
  }
  
  return youths;
}

void youth_t_free(youth_t *youth) {
  uint32_t i;

  for(i = 0; i < youth->num_sides; i++) 
    free(youth->sides_of_city[i]);
  free(youth->sides_of_city);
  free(youth->career_interest1);
  free(youth->career_interest2);
  for(i = 0; i < youth->num_skills; i++)
    free(youth->skills[i]);
  free(youth->skills);
  free(youth->second_language);
  free(youth->school_status);
  free(youth->highest_grade_completed);
  free(youth);
}

void free_youth_list(youths_t *youths) {
  for(uint32_t i = 0; i < youths->nLength; i++) {
    youth_t_free(youths->pList[i]);
  }
  youths_t_free(youths);
  free(youths);
}
