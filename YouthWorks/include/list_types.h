#ifndef LIST_TYPES_H
#define LIST_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define NO_ERROR 0
#define MEM_ERR 255

/*----------------------TYPE Parameterized List------------------------------------*/
#define create_list_headers(NAME,TYPE)                                             \
typedef struct NAME {                                                              \
  uint32_t nLength;                                                                \
  uint32_t nLength_max;                                                            \
  TYPE *pList;                                                                     \
  uint32_t nResizeAmt;                                                             \
} NAME;                                                                            \
                                                                                   \
NAME *NAME##_alloc(uint32_t length, uint32_t resize_amt);                          \
uint8_t NAME##_init(NAME *x, uint32_t length, uint32_t resize_amt);                \
uint8_t NAME##_resize(NAME *x, uint32_t new_length);                               \
uint8_t NAME##_push(NAME *x, TYPE value);                                          \
uint8_t NAME##_update(NAME *x, uint32_t index, TYPE value);                        \
TYPE NAME##_at(NAME *x, uint32_t index);                                           \
void NAME##_copy(NAME *dst, NAME *src);                                            \
void NAME##_free(NAME *x);                                                         \

create_list_headers(uint8_t_list, uint8_t)
create_list_headers(int8_t_list, int8_t)
create_list_headers(uint16_t_list, uint16_t)
create_list_headers(int16_t_list, int16_t)
create_list_headers(uint32_t_list, uint32_t)
create_list_headers(int32_t_list, int32_t)
create_list_headers(uint64_t_list, uint64_t)
create_list_headers(int64_t_list, int64_t)
create_list_headers(uintmax_t_list, uintmax_t)
create_list_headers(intmax_t_list, intmax_t)
create_list_headers(uintptr_t_list, uintptr_t)

create_list_headers(uint8_t_plist, uint8_t *)
create_list_headers(int8_t_plist, int8_t *)
create_list_headers(uint16_t_plist, uint16_t *)
create_list_headers(int16_t_plist, int16_t *)
create_list_headers(uint32_t_plist, uint32_t *)
create_list_headers(int32_t_plist, int32_t *)
create_list_headers(uint64_t_plist, uint64_t *)
create_list_headers(int64_t_plist, int64_t *)
create_list_headers(uintmax_t_plist, uintmax_t *)
create_list_headers(intmax_t_plist, intmax_t *)
create_list_headers(uintptr_t_plist, uintptr_t *)

/*---------------------------------------TYPE Parameterized List----------------------------------------------------------------------*/
#define create_list_type(NAME,TYPE)                                                                                                   \
NAME *NAME##_alloc(uint32_t length, uint32_t resize_amt) {                                                                            \
  NAME *x = malloc(sizeof(NAME));                                                                                                     \
  if(NAME##_init(x, length, resize_amt) == NO_ERROR)                                                                                  \
    return x;                                                                                                                         \
  return NULL;                                                                                                                        \
}                                                                                                                                     \
                                                                                                                                      \
uint8_t NAME##_init(NAME *x, uint32_t length, uint32_t resize_amt) {                                                                  \
  length = length==0?1:length;                                                                                                        \
  resize_amt = resize_amt == 0?1:resize_amt;                                                                                          \
  x->nLength = 0;                                                                                                                     \
  x->nLength_max = length;                                                                                                            \
  x->pList = (TYPE *)calloc(x->nLength_max, sizeof(TYPE));                                                                            \
  if(x->pList == NULL) {                                                                                                              \
    return MEM_ERR;                                                                                                                   \
  }                                                                                                                                   \
  x->nResizeAmt = resize_amt;                                                                                                         \
  return NO_ERROR;                                                                                                                    \
}                                                                                                                                     \
                                                                                                                                      \
uint8_t NAME##_resize(NAME *x, uint32_t new_length) {                                                                                 \
  if(new_length > x->nLength_max) {                                                                                                   \
    uint32_t delta = new_length - x->nLength_max;                                                                                     \
    if(delta < x->nResizeAmt) new_length = x->nLength_max + delta;                                                                    \
    x->nLength_max=new_length;                                                                                                        \
    x->pList = (TYPE *)realloc((void*)x->pList, x->nLength_max * sizeof(TYPE));                                                       \
    if(x->pList==NULL) {                                                                                                              \
      return MEM_ERR;                                                                                                                 \
    }                                                                                                                                 \
  }                                                                                                                                   \
  return NO_ERROR;                                                                                                                    \
}                                                                                                                                     \
                                                                                                                                      \
uint8_t NAME##_push(NAME *x, TYPE value) {                                                                                            \
  if(NAME##_resize(x, x->nLength+1) == MEM_ERR) return MEM_ERR;                                                                       \
  x->pList[x->nLength++] = value;                                                                                                     \
  return NO_ERROR;                                                                                                                    \
}                                                                                                                                     \
                                                                                                                                      \
TYPE NAME##_peek(NAME *x) {                                                                                                           \
  return x->pList[x->nLength];                                                                                                        \
}                                                                                                                                     \
                                                                                                                                      \
uint8_t NAME##_update(NAME *x, uint32_t index, TYPE value) {                                                                          \
  if(NAME##_resize(x, index+1) == MEM_ERR) return MEM_ERR;                                                                            \
  x->pList[index] = value;                                                                                                            \
  if(x->nLength <= index) x->nLength = index+1;                                                                                       \
  return NO_ERROR;                                                                                                                    \
}                                                                                                                                     \
                                                                                                                                      \
TYPE NAME##_at(NAME *x, uint32_t index) {                                                                                             \
  assert(x->nLength > index);                                                                                                         \
  return x->pList[index];                                                                                                             \
}                                                                                                                                     \
                                                                                                                                      \
void NAME##_copy(NAME *dst, NAME *src) {                                                                                              \
  NAME##_resize(dst, src->nLength);                                                                                                   \
  dst->nLength = src->nLength;                                                                                                        \
  memcpy(dst->pList, src->pList, dst->nLength * sizeof(TYPE));                                                                        \
}                                                                                                                                     \
                                                                                                                                      \
void NAME##_free(NAME *x) {                                                                                                           \
  if(x->pList == NULL) return;                                                                                                        \
  free((void *)x->pList);                                                                                                             \
  x->pList = NULL;                                                                                                                    \
  x->nLength = 0;                                                                                                                     \
  x->nLength_max = 0;                                                                                                                 \
}                                                                                                                                     \

#endif
