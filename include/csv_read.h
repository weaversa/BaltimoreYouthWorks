#ifndef CSVREAD_H
#define CSVREAD_H

#include "youthworks.h"

typedef struct csv_data {
  uint32_t nRows;
  uint32_t nMaxRows;
  uint8_t_plist *pRow;
} csv_data;

char* stradd(const char* a, const char* b);
void write_csv(FILE *fout, csv_data *pCSVData);
void csv_data_free(csv_data *pCSVData);
csv_data *csv_read_file(char *filename);
csv_data *csv_read_buffer(char *buf, size_t num_bytes);

#endif
