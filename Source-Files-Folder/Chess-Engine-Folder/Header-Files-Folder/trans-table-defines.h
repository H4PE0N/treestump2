
#ifndef TRANS_TABLE_DEFINES_H
#define TRANS_TABLE_DEFINES_H

typedef enum EFlag
{
  EFLAG_EXACT, EFLAG_LOWER, EFLAG_UPPER
} EFlag;

typedef struct Entry
{
  uint64_t hash;
  int depth;
  int score;
  EFlag flag;
} Entry;

extern const int HASH_TABLE_SIZE;

#endif
