#include "youthworks.h"

//A utility function for adding newlines to single rows. Necessary for
//the row to parse correctly with csv_parse.
char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
}

csv_data *csv_data_init() {
  csv_data *pCSVData = (csv_data *)malloc(1*sizeof(csv_data));
  pCSVData->pRow = (uint8_t_plist *)malloc((pCSVData->nMaxRows = 10)*sizeof(uint8_t_plist));
  pCSVData->nRows = 1;
  uint8_t_plist_init(&pCSVData->pRow[0], 1, 1);
  return pCSVData;
}

void csv_data_free(csv_data *pCSVData) {
  uint32_t i, j;
  for(i = 0; i < pCSVData->nRows; i++) {
    uint8_t_plist *pRow = &pCSVData->pRow[i];
    for(j = 0; j  < pRow->nLength; j++) {
      if(pRow->pList[j] != NULL)
        free(pRow->pList[j]);
    }
    uint8_t_plist_free(pRow);
  }
  free(pCSVData->pRow);
  pCSVData->pRow = NULL;
  pCSVData->nRows = 0;
  free(pCSVData);
}

void write_csv(FILE *fout, csv_data *pCSVData) {
  uint32_t i, j;
  for(i = 0; i < pCSVData->nRows; i++) {
    if(pCSVData->pRow[i].nLength == 0) continue;
    for(j = 0; j < pCSVData->pRow[i].nLength-1; j++) {
      fprintf(fout, "%s, ", (char *)uint8_t_plist_at(&pCSVData->pRow[i], j));
    }
    fprintf(fout, "%s\n", (char *)uint8_t_plist_at(&pCSVData->pRow[i], j));
  }
}

void clean_csv(csv_data *pCSVData) {
  //Cleanup empty rows, etc.
  uint32_t i, j, k;
  for(i = 0, j = 0; i < pCSVData->nRows; i++) {
    pCSVData->pRow[j++] = pCSVData->pRow[i];
    uint8_t *cell = uint8_t_plist_at(&pCSVData->pRow[i], 0);
    if(cell == NULL || cell[0] == 0) {
      //fprintf(stderr, "|delete %u|", i);
      uint8_t_plist *pRow = &pCSVData->pRow[i];
      for(k = 0; k < pRow->nLength; k++) {
        if(pRow->pList[k] != NULL)
          free(pRow->pList[k]);
      }
      uint8_t_plist_free(pRow);
      j--;
    }
  }
  pCSVData->nRows = j;
  //fprintf(stderr, "|%u|", j);
}

//read new cell
void cb1 (void *s, size_t len, void *data) {
  csv_data *pCSVData = (csv_data *)data;
  uint8_t *cell = malloc(len+1);
  memcpy(cell, s, len);
  cell[len] = 0; //NULL terminate

  /* Replace "" with commas */
  for(size_t i = 0; i < len; i++) {
    if(cell[i] == 13) cell[i] = ',';
  }
  //When these multi-element strings occur, could recurse and call
  //csv_parse to break them apart.
  
  uint8_t_plist_push(&pCSVData->pRow[pCSVData->nRows-1], cell);
}

//read new row
void cb2 (int c, void *data) {
  csv_data *pCSVData = (csv_data *)data;

  if(pCSVData->nRows >= pCSVData->nMaxRows) {
    pCSVData->pRow = (uint8_t_plist *)realloc(pCSVData->pRow, (pCSVData->nMaxRows += 10)*sizeof(uint8_t_plist));
  }

  uint8_t_plist_init(&pCSVData->pRow[pCSVData->nRows], 1, 1);
  pCSVData->nRows++;
}

csv_data *csv_read_file(char *filename) {
  uint8_t wellformed = 1;
  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open %s: %s, skipping\n", filename, strerror(errno));
    return NULL;
  }

  struct csv_parser *pCSVParser = (struct csv_parser *)malloc(1*sizeof(struct csv_parser));
  if (csv_init(pCSVParser, CSV_STRICT) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(0);
  }

  csv_data *pCSVData = csv_data_init();
  
  size_t pos = 0;
  size_t bytes_read;
  char buf[1026];
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    size_t retval;
    if(bytes_read != 1024) {
      buf[bytes_read++] = '\n';
      buf[bytes_read++] = ',';
    }
    if ((retval = csv_parse(pCSVParser, buf, bytes_read, cb1, cb2, (void *)pCSVData)) != bytes_read) {
      if (csv_error(pCSVParser) == CSV_EPARSE) {
        printf("%s: malformed at byte %lu\n", filename, (unsigned long)pos + retval + 1);
        wellformed = 0;
        break;
      } else {
        printf("Error while processing %s: %s\n", filename, csv_strerror(csv_error(pCSVParser)));
        wellformed = 0;
        break;
      }
    }
    pos += bytes_read;
  }
  if(!wellformed) {
    printf("%s not well-formed...exiting\n", filename);
    //Admittedly, this is probably not an exitable offense, in general.
    exit(0);
  }
  
  fclose(fp);
  csv_fini(pCSVParser, NULL, NULL, NULL);
  csv_free(pCSVParser);
  free(pCSVParser);

  //Remove empty rows, etc.
  clean_csv(pCSVData);
   
  return pCSVData;
}

csv_data *csv_read_buffer(char *buf, size_t num_bytes) {
  uint8_t wellformed = 1;
  struct csv_parser *pCSVParser = (struct csv_parser *)malloc(1*sizeof(struct csv_parser));
  if (csv_init(pCSVParser, CSV_STRICT) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(0);
  }

  csv_data *pCSVData = csv_data_init();
  
  size_t retval;
  if ((retval = csv_parse(pCSVParser, buf, num_bytes, cb1, cb2, (void *)pCSVData)) != num_bytes) {
    if (csv_error(pCSVParser) == CSV_EPARSE) {
      printf("Recursive CSV parse found malformed at byte %lu\n", retval + 1);
      wellformed = 0;
    } else {
      printf("Error while processing recursive CVS parse: %s\n", csv_strerror(csv_error(pCSVParser)));
      wellformed = 0;
    }
  }
  if(!wellformed) {
    printf("Recursive CSV parse not well-formed...exiting\n");
    //Admittedly, this is probably not an exitable offense, in general.
    exit(0);
  }
  
  csv_fini(pCSVParser, NULL, NULL, NULL);
  csv_free(pCSVParser);
  free(pCSVParser);
  
  return pCSVData;
}
